#include "TwitchChannelFeed.h"
#include "TwitchChannels.h"
#include "JsonWrapper.h"

TwitchXX::TwitchChannelFeed::~TwitchChannelFeed()
{
}

TwitchXX::TwitchPostsContainer TwitchXX::TwitchChannelFeed::GetPosts(const std::wstring & channel_name, size_t limit) const
{
	web::uri_builder first_builder(U("/feed/") + channel_name + U("/posts"));
	first_builder.append_query(U("limit"), 100); //TODO: Check perfomance!
	web::uri_builder builder(first_builder);
	size_t count = 0;
	std::wstring cursor;
	TwitchPostsContainer result;
	for (;;)
	{
		auto value = (*_request)(builder.to_uri());
		if (value.is_null() || _request->status_code() != web::http::status_codes::OK)
		{
			break;
		}

		count = value.at(U("_total")).as_number().to_uint32();
		limit = limit == 0 ? count : limit;
		cursor = value.at(U("_cursor")).as_string();
		auto posts = value.at(U("posts"));
		if (posts.is_null() || !posts.is_array())
		{
			break;
		}
		for each (const auto& post_descriptor in posts.as_array())
		{
			result.insert(Create<TwitchPost>(post_descriptor));
		}

		if (result.size() >= count || (limit > 0 && result.size() >= limit))
		{
			break;
		}

		builder = { first_builder };
		builder.append_query(U("cursor"), cursor);
	}
	return TwitchPostsContainer{ result.begin(),std::next(result.begin(),std::min(result.size(),limit)) };
}

TwitchXX::TwitchPost TwitchXX::TwitchChannelFeed::GetPost(const std::wstring & channel_name, size_t id) const
{
	std::wstringstream  ss;
	ss << id;
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts/") + ss.str());
	auto response = (*_request)(builder.to_uri());

	return Create<TwitchPost>(response);
}

TwitchXX::TwitchPost TwitchXX::TwitchChannelFeed::Post(const std::wstring& channel_name, const std::wstring & body, bool share) const
{
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts"));
	builder.append_query(U("content"), body);
	builder.append_query(U("share"), share);

	auto response = (*_request)(builder.to_uri(), web::http::methods::POST);

	return Create<TwitchPost>(response);
}

bool TwitchXX::TwitchChannelFeed::DeletePost(const std::wstring & channel_name, size_t id) const
{
	std::wstringstream ss;
	ss << id;
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts/") + ss.str());
	auto response = (*_request)(builder.to_uri(),web::http::methods::DEL);

	return _request->status_code() == web::http::status_codes::OK;
}

bool TwitchXX::TwitchChannelFeed::AddReaction(const std::wstring& channel_name, size_t id, size_t emote_id) const
{
	std::wstringstream ss_id;
	ss_id << id;
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts/") + ss_id.str() + U("/reactions"));
	if(emote_id)
	{
		builder.append_query(U("emote_id"), emote_id);
	}
	else
	{
		builder.append_query(U("emote_id"), U("endorse"));
	}

	auto response = (*_request)(builder.to_uri(), web::http::methods::POST);

	return _request->status_code() == web::http::status_codes::OK;
}

bool TwitchXX::TwitchChannelFeed::RemoveReaction(const std::wstring& channel_name, size_t id, size_t emote_id) const
{
	std::wstringstream ss_id;
	ss_id << id;
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts/") + ss_id.str() + U("/reactions"));
	if (emote_id)
	{
		builder.append_query(U("emote_id"), emote_id);
	}
	else
	{
		builder.append_query(U("emote_id"), U("endorse"));
	}

	auto response = (*_request)(builder.to_uri(), web::http::methods::DEL);

	return _request->status_code() == web::http::status_codes::OK;
}

template <> 
TwitchXX::TwitchPost TwitchXX::Create<TwitchXX::TwitchPost>(const web::json::value& value)
{
	TwitchPost post;
	JsonWrapper wrapper(value);

	post.Id(*wrapper[U("_id")]);
	post.Created(*wrapper[U("created_at")]);
	post.Deleted(*wrapper[U("deleted")]);
	//post.Emotes(*wrapper[U("emotes")]);
	auto endorse_json = value.at(U("reqctions")).at(U("endorse"));
	post.EndorsedCount(endorse_json.at(U("count")).as_number().to_uint32());
	auto users_ids_json = endorse_json.at(U("user_ids"));
	if (!users_ids_json.is_null() && users_ids_json.is_array())
	{
		auto user_ids = users_ids_json.as_array();
		std::set<std::wstring> ids;
		//std::copy(user_ids.begin(), user_ids.end(), std::inserter(ids, ids.begin()));
		std::for_each(user_ids.begin(), user_ids.end(), [&ids](const web::json::value& id) { ids.insert(id.as_string()); });
		post.EndorsedUsers(ids);
	}
	post.Body(*wrapper[U("body")]);
	post.Author(Create<TwitchUser>(value.at(U("user"))));
	post.Tweet(*wrapper[U("tweet")]);

	return post;
}
