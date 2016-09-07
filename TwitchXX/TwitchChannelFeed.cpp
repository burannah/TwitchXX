#include "TwitchChannelFeed.h"
#include "TwitchChannels.h"
#include "JsonWrapper.h"
#include "TwitchException.h"
#include "TwitchUsers.h"

TwitchXX::TwitchPostsContainer TwitchXX::TwitchChannelFeed::GetPosts(const std::wstring & channel_name, size_t limit) const
{
	web::uri_builder first_builder(U("/feed/") + channel_name + U("/posts"));
	first_builder.append_query(U("limit"), limit == 0 ? 100 : limit);
	return GetObjectsArrayByNext<TwitchPost>(first_builder, U("posts"));
}

TwitchXX::TwitchPost TwitchXX::TwitchChannelFeed::GetPost(const std::wstring & channel_name, unsigned long long id) const
{
	std::wstringstream  ss;
	ss << id;
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts/") + ss.str());
	auto response = _request->get(builder.to_uri());
	return Create<TwitchPost>(response);
}

TwitchXX::TwitchPost TwitchXX::TwitchChannelFeed::Post(const std::wstring& channel_name, const std::wstring & body, bool share) const
{
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts"));

	web::json::value request_body;
	request_body[U("content")] = web::json::value::string(body);
	request_body[U("share")] = web::json::value::boolean(share);

	auto response = _request->post(builder.to_uri(), request_body);
	if(_request->status_code()!= web::http::status_codes::OK)
	{
		throw TwitchException("Unable to create post!", _request->status_code());
	}
	auto post = Create<TwitchPost>(response[U("post")]);
	auto tweet = response[U("tweet")];
	if(!tweet.is_null())
	{
		post.Tweet.Set(response[U("tweet")].as_string());
	}

	return post;
}

bool TwitchXX::TwitchChannelFeed::DeletePost(const std::wstring & channel_name, unsigned long long id) const
{
	std::wstringstream ss;
	ss << id;
	web::uri_builder builder(U("/feed/") + channel_name + U("/posts/") + ss.str());
	auto response = _request->del(builder.to_uri());

	return _request->status_code() == web::http::status_codes::OK;
}

bool TwitchXX::TwitchChannelFeed::AddReaction(const std::wstring& channel_name, unsigned long long id, size_t emote_id) const
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

	auto response = _request->post(builder.to_uri());

	return _request->status_code() == web::http::status_codes::OK;
}

bool TwitchXX::TwitchChannelFeed::RemoveReaction(const std::wstring& channel_name, unsigned long long id, size_t emote_id) const
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

	auto response = _request->del(builder.to_uri());

	return _request->status_code() == web::http::status_codes::OK;
}

template <> 
TwitchXX::TwitchPost TwitchXX::Create<TwitchXX::TwitchPost>(const web::json::value& value)
{
	TwitchPost post;
	JsonWrapper wrapper(value);

	post.Id.Set(*wrapper[U("id")]);
	post.Created.from_string(*wrapper[U("created_at")]);
	post.Deleted.Set(*wrapper[U("deleted")]);
	//post.Emotes(*wrapper[U("emotes")]);
	if(value.has_field(U("reactions")) && !value.at(U("reactions")).is_null() && value.at(U("reactions")).size())
	{
		auto endorse_json = value.at(U("reactions")).at(U("endorse"));
		post.Endorsed_Count.Set(endorse_json.at(U("count")).as_number().to_uint32());
		auto users_ids_json = endorse_json.at(U("user_ids"));
		if (!users_ids_json.is_null() && users_ids_json.is_array())
		{
			auto user_ids = users_ids_json.as_array();
			std::set<unsigned long long> ids;
			//std::copy(user_ids.begin(), user_ids.end(), std::inserter(ids, ids.begin()));
			std::for_each(user_ids.begin(), user_ids.end(), [&ids](const web::json::value& id) { ids.insert(id.as_number().to_uint64()); });
			post.Endorsed_Users = ids;
		}
	}
	post.Body.Set(*wrapper[U("body")]);
	post.Author = Create<TwitchUser>(value.at(U("user")));

	return post;
}
