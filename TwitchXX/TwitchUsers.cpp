﻿#include "TwitchUser.h"
#include <cpprest/details/basic_types.h>
#include <cpprest/http_msg.h>
#include "TwitchUsers.h"
#include "JsonWrapper.h"
#include "TwitchException.h"

TwitchXX::TwitchBlockedUsersContainer TwitchXX::TwitchUsers::GetBlocked(const std::wstring& user_name) const
{
	web::uri_builder builder{U("/users/") + user_name + U("/blocks")};
	builder.append_query(U("limit"), 100); //TODO: Check perfomance!
	size_t count = 0;
	std::wstring cursor;
	TwitchXX::TwitchBlockedUsersContainer result;
	for (;;)
	{
		auto value = (*_request)(builder.to_uri());
		if (value.is_null() || _request->status_code() != web::http::status_codes::OK)
		{
			break;
		}

		auto blocks = value.at(U("blocks"));
		if (blocks.is_null() || !blocks.is_array())
		{
			break;
		}
		for each (const auto& block_descriptor in blocks.as_array())
		{
			result.insert(Create<TwitchBlockedUser>(block_descriptor));
		}

		auto next = value.at(U("_links")).at(U("next"));
		if (!next.is_null() && next.is_string())
		{
			builder = web::uri_builder(next.as_string());
		}
		else
		{
			break;
		}
	}
	return result;

}

TwitchXX::TwitchBlockedUser TwitchXX::TwitchUsers::BlockUser(const std::wstring& user_name, const std::wstring& target_name) const
{
	web::uri_builder builder{U("/users/") + user_name + U("/blocks/") + target_name};

	auto response = (*_request)(builder.to_uri(), web::http::methods::PUT);
	if (_request->status_code() != web::http::status_codes::OK)
	{
		throw TwitchException("Unable to block a user", _request->status_code());
	}
	return Create<TwitchBlockedUser>(response);
}

bool TwitchXX::TwitchUsers::UblockUser(const std::wstring& user_name, const std::wstring& target_name) const
{
	web::uri_builder builder{ U("/users/") + user_name + U("/blocks/") + target_name };

	auto response = (*_request)(builder.to_uri(), web::http::methods::DEL);
	switch(_request->status_code())
	{
	case web::http::status_codes::NoContent:
		return true;
	case web::http::status_codes::NotFound://User is not on block list
	case 422: // Unprocessable Entity
		return false;
	}
	throw TwitchException{ "Unexpeced result on delete user from block list!", _request->status_code() };
}

template <>
TwitchXX::TwitchBlockedUser TwitchXX::Create<TwitchXX::TwitchBlockedUser>(const web::json::value& value)
{
	JsonWrapper wrapper(value);
	TwitchBlockedUser result;
	result.BlockedId(*wrapper[U("_id")]);
	result.BlockUpdated(*wrapper[U("updated_at")]);
	result.User(Create<TwitchUser>(value.at(U("user"))));
	return result;
}


template<>
TwitchXX::TwitchUser TwitchXX::Create(const web::json::value & value)
{
	TwitchUser user;
	JsonWrapper wrapper(value);

	user.Created(*wrapper[U("created_at")]);
	user.Name(*wrapper[U("name")]);
	user.Updated(*wrapper[U("updated_at")]);
	user.Id(*wrapper[U("_id")]);
	user.DisplayName(*wrapper[U("display_name")]);
	user.Logo(*wrapper[U("logo")]);
	user.Type(*wrapper[U("type")]);
	user.Bio(*wrapper[U("bio")]);

	return user;
}