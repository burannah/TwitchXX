#include "TwitchUser.h"
#include <cpprest/details/basic_types.h>
#include <cpprest/http_msg.h>
#include "TwitchUsers.h"
#include "JsonWrapper.h"
#include "TwitchException.h"
#include "TwitchFollower.h"
#include "TwitchChannels.h"
#include <bitset>
#include "TwitchChat.h"

std::map<TwitchXX::AuthScope, std::wstring> TwitchXX::TwitchUsers::Scopes = {
	{AuthScope::USER_READ,U("user_read")},
	{AuthScope::USER_BLOCKS_EDIT,U("user_blocks_edit")},
	{AuthScope::USER_BLOCKS_READ,U("user_blocks_read")},
	{AuthScope::USER_FOLLOWS_EDIT,U("user_follows_edit")},
	{AuthScope::CHANNEL_READ,U("channel_read")},
	{AuthScope::CHANNEL_EDITOR,U("channel_editor")},
	{AuthScope::CHANNEL_COMMERCIAL,U("channel_commercial")},
	{AuthScope::CHANNEL_STREAM,U("channel_stream")},
	{AuthScope::CHANNEL_SUBSCRIPTIONS,U("channel_subscriptions")},
	{AuthScope::USER_SUBSCRIPTIONS,U("user_subscriptions")},
	{AuthScope::CHANNEL_CHECK_SUBSCRIPTION,U("channel_check_subscription")},
	{AuthScope::CHAT_LOGIN,U("chat_login")},
	{AuthScope::CHANNEL_FEED_READ,U("channel_feed_read")},
	{AuthScope::CHANNEL_FEED_EDIT,U("channel_feed_edit")}
};

std::map<std::wstring, TwitchXX::AuthScope> TwitchXX::TwitchUsers::Rscopes = {};


TwitchXX::TwitchBlockedUsersContainer TwitchXX::TwitchUsers::GetBlocked(const std::wstring& user_name) const
{
	static const size_t limit = 100;
	web::uri_builder builder{U("/users/") + user_name + U("/blocks")};
	builder.append_query(U("limit"), limit); //TODO: Check perfomance!
	return GetObjectsArrayByNext<TwitchBlockedUser>(builder, U("blocks"));
}

TwitchXX::TwitchBlockedUser TwitchXX::TwitchUsers::BlockUser(const std::wstring& user_name, const std::wstring& target_name) const
{
	web::uri_builder builder{U("/users/") + user_name + U("/blocks/") + target_name};
	auto response = _request->put(builder.to_uri());
	return Create<TwitchBlockedUser>(response);
}

bool TwitchXX::TwitchUsers::UblockUser(const std::wstring& user_name, const std::wstring& target_name) const
{
	web::uri_builder builder{ U("/users/") + user_name + U("/blocks/") + target_name };

	try
	{
		auto response = _request->del(builder.to_uri());
	}
	catch(TwitchException&)
	{
		switch (_request->status_code())
		{
		case web::http::status_codes::NoContent:
			return true;
		case web::http::status_codes::NotFound://User is not on block list
		case 422: // Unprocessable Entity
			return false;
		default:
			throw;
		}
	}
	throw TwitchException{ "Unexpeced result on delete user from block list!", _request->status_code() };
}

TwitchXX::TwitchFollowedChannelsContainer TwitchXX::TwitchUsers::GetFollowingChannels(const std::wstring& user_name, TwitchXX::Sort_Order order ) const
{
	web::uri_builder builder{ U("/users/") + user_name + U("/follows/channels") };
	builder.append_query(U("limit"), 100);
	//builder.append_query(U("sortby"), Sort_Order_To_string(order));
	return GetObjectsArrayByNext<TwitchFollowedChannel>(builder, U("follows"));
}

TwitchXX::TwitchFollowedChannel TwitchXX::TwitchUsers::GetFollowingChannel(const std::wstring & user_name, const std::wstring & channel_name) const
{
	web::uri_builder builder{ U("/users/") + user_name + U("/follows/channels/") + channel_name };

	try
	{
		auto response = _request->get(builder.to_uri());
		return Create<TwitchFollowedChannel>(response);
	}
	catch (TwitchException& e)
	{
		if (e.code() == web::http::status_codes::NotFound)
		{
			throw TwitchException("User is not follow target channel", 404);
		}
		else
		{
			throw;
		}
	}
}

TwitchXX::TwitchFollowedChannel TwitchXX::TwitchUsers::FollowChannel(const std::wstring& user_name, const std::wstring & channel_name, bool notification) const
{
	try
	{
		web::uri_builder builder{ U("/users/") + user_name + U("/follows/channels/") + channel_name };
		if (notification)
		{
			builder.append_query(U("notifications"), U("true"));
		}

		auto response = _request->put(builder.to_uri());
		return Create<TwitchFollowedChannel>(response);
	}
	catch (TwitchException& e)
	{
		if (e.code() == 422)
		{
			throw TwitchException("Update failed", 422);
		}
		throw;
	}

}

void TwitchXX::TwitchUsers::UnfollowChannel(const std::wstring & user_name, const std::wstring & channel_name) const
{
	try
	{
		web::uri_builder builder{ U("/users/") + user_name + U("/follows/channels/") + channel_name };
		auto response = _request->del(builder.to_uri());
	}
	catch (TwitchException& e)
	{
		switch (e.code())
		{
		case web::http::status_codes::NoContent:
			//Successfull
			return;
		case 422:
			throw TwitchException("Delete failed", 422);
		default:
			throw;
		}
	}
}

TwitchXX::AuthToken TwitchXX::TwitchUsers::GetCurrentUserStatus() const
{
	try
	{
		web::uri_builder builder;
		auto response = _request->get(builder.to_uri());
		if (response.has_field(U("token")))
		{
			auto token = response.at(U("token"));
			if (token.has_field(U("valid")) && token.at(U("valid")).as_bool())
			{
				return Create<AuthToken>(token);
			}
			throw TwitchException("Not authorized!", _request->status_code());
		}
		throw TwitchException("Unknown response", _request->status_code());
	}
	catch (TwitchException& e)
	{
		throw TwitchException("User status error. Not authorized?", e.code());
	}
}

TwitchXX::TwitchFollowedChannel TwitchXX::TwitchUsers::GetUserSubscribedChannel(const std::wstring& channel_name, const std::wstring& user_name) const
{
	try
	{
		web::uri_builder builder{ U("/users/") + user_name + U("/subscriptions/") + channel_name };
		auto response = _request->get(builder.to_uri());
		return Create<TwitchFollowedChannel>(response);
	}
	catch (TwitchException& e)
	{
		switch (e.code())
		{
		case 422:
			throw TwitchException("Channel has no subscription program.", 422);
		case web::http::status_codes::NotFound:
			throw TwitchException("User is not subscribed!", e.code());
		default:
			throw;
		}
	}

}

TwitchXX::TwitchUser TwitchXX::TwitchUsers::GetUser(const std::wstring& user_name) const
{
	web::uri_builder builder(U("/users/") + user_name);
	return GetSingleObject<TwitchUser>(builder.to_uri());
}

std::set<TwitchXX::EmoticonImage> TwitchXX::TwitchUsers::GetUserEmoticons(const std::wstring& user_name) const
{
	web::uri_builder builder(U("/users/") + user_name + U("/emotes"));
	auto resposne = _request->get(builder.to_uri());
	auto emoticon_sets = resposne.at(U("emoticon_sets"));
	return TwitchChat::ParseEmoticonSets(emoticon_sets);
}

TwitchXX::TwitchUser TwitchXX::TwitchUsers::GetCurrentUser() const
{
	web::uri_builder builder(U("/user"));
	return GetSingleObject<TwitchUser>(builder.to_uri());
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
TwitchXX::TwitchUser TwitchXX::Create<TwitchXX::TwitchUser>(const web::json::value & value)
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

template <>
TwitchXX::AuthToken TwitchXX::Create<TwitchXX::AuthToken>(const web::json::value& value)
{
	AuthToken status;
	JsonWrapper w(value);
	status.Name.Set(*w[U("user_name")]);
	status.Valid.Set(*w[U("valid")]);

	JsonWrapper a(value.at(U("authorization")));

	status.Created.from_string(*a[U("created_at")]);
	status.Updated.from_string(*a[U("updated_at")]);

	AuthScope scope = {};

	if(TwitchUsers::Rscopes.size() == 0)
	{
		for (const auto& entry : TwitchUsers::Scopes)
		{
			TwitchUsers::Rscopes[entry.second] = entry.first;
		}
	}

	auto json_scopes = value.at(U("authorization")).at(U("scopes")).as_array();
	for (const auto& s : json_scopes)
	{
#ifdef _DEBUG
		if(TwitchUsers::Rscopes.find(s.as_string()) == TwitchUsers::Rscopes.end())
		{
			throw TwitchException("Unknown scope!");
		}
#endif
		scope = scope | TwitchUsers::Rscopes[s.as_string()];
	}
	status.AuthorizationScopes.Set(scope);

	return status;
}
