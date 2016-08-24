#include "TwitchUser.h"
#include <cpprest/details/basic_types.h>
#include <cpprest/http_msg.h>
#include "TwitchUsers.h"
#include "JsonWrapper.h"
#include "TwitchException.h"
#include "TwitchFollower.h"
#include "TwitchChannels.h"

TwitchXX::TwitchBlockedUsersContainer TwitchXX::TwitchUsers::GetBlocked(const std::wstring& user_name) const
{
	static const size_t limit = 100;
	web::uri_builder builder{U("/users/") + user_name + U("/blocks")};
	builder.append_query(U("limit"), limit); //TODO: Check perfomance!
	size_t count = 0;
	std::wstring cursor;
	TwitchXX::TwitchBlockedUsersContainer result;
	for (;;)
	{
		auto value = (*_request)(builder.to_uri());

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
		if (blocks.size() == limit && !next.is_null() && next.is_string())
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
	return Create<TwitchBlockedUser>(response);
}

bool TwitchXX::TwitchUsers::UblockUser(const std::wstring& user_name, const std::wstring& target_name) const
{
	web::uri_builder builder{ U("/users/") + user_name + U("/blocks/") + target_name };

	try
	{
		auto response = (*_request)(builder.to_uri(), web::http::methods::DEL);
	}
	catch(TwitchException e)
	{
		switch (_request->status_code())
		{
		case web::http::status_codes::NoContent:
			return true;
		case web::http::status_codes::NotFound://User is not on block list
		case 422: // Unprocessable Entity
			return false;
		}
	}
	throw TwitchException{ "Unexpeced result on delete user from block list!", _request->status_code() };
}

TwitchXX::TwitchFollowedChannelsContainer TwitchXX::TwitchUsers::GetFollowingChannels(const std::wstring& user_name, TwitchXX::Sort_Order order ) const
{
	web::uri_builder builder{ U("/users/") + user_name + U("/follows/channels") };
	builder.append_query(U("limit"), 100);
	//builder.append_query(U("sortby"), Sort_Order_To_string(order));
	TwitchFollowedChannelsContainer result;

	while(true)
	{
		web::json::value value;
		try
		{
			value = (*_request)(builder.to_uri());
		}
		catch (TwitchException e)
		{
			if(e.code() == web::http::status_codes::NotFound)
			{
				break;
			}
		}
		if(value.is_null() || !value.has_field(U("follows")) || !value[U("follows")].is_array())
		{
			break;
		}

		for (const auto& follow : value[U("follows")].as_array())
		{
			result.insert(Create<TwitchFollowedChannel>(follow));
		}

		if(value.has_field(U("_links"))&&value[U("_links")].has_field(U("next")))
		{
			builder = web::uri_builder(value[U("_links")][U("next")].as_string());
		}
		else
		{
			break;
		}
	}

	return result;


}

template <>
TwitchXX::TwitchBlockedUser TwitchXX::Create<TwitchXX::TwitchBlockedUser>(const web::json::value& value)
{
	JsonWrapper wrapper(value);
	TwitchBlockedUser result;
	result.Block_Id.Set(*wrapper[U("_id")]);
	result.Block_Updated.from_string(*wrapper[U("updated_at")]);
	result.User = Create<TwitchUser>(value.at(U("user")));
	return result;
}


template<>
TwitchXX::TwitchUser TwitchXX::Create(const web::json::value & value)
{
	TwitchUser user;
	JsonWrapper wrapper(value);

	user.Created.from_string(*wrapper[U("created_at")]);
	user.Name.Set(*wrapper[U("name")]);
	user.Updated.from_string(*wrapper[U("updated_at")]);
	user.Id.Set(*wrapper[U("_id")]);
	user.Display_Name.Set(*wrapper[U("display_name")]);
	user.Logo.Set(*wrapper[U("logo")]);
	user.Type.Set(*wrapper[U("type")]);
	user.Bio.Set(*wrapper[U("bio")]);

	return user;
}

template <>
TwitchXX::TwitchFollowedChannel TwitchXX::Create<TwitchXX::TwitchFollowedChannel>(const web::json::value& value)
{
	TwitchFollowedChannel follow;
	JsonWrapper wrapper(value);

	follow.Created.from_string(*wrapper[U("created_at")]);
	follow.Notifications.Set(*wrapper[U("notifications")]);

	follow.Channel = Create<TwitchChannel>(value.at(U("channel")));

	return  follow;
}
