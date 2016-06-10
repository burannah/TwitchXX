#pragma once
#include <string>
#include "TwitchRequest.h"
#include "TwitchPost.h"
namespace TwitchXX
{
	class TwitchChannelFeed : TwitchRequest<TwitchPost>
	{
	public:
		TwitchChannelFeed() {} ;
		virtual ~TwitchChannelFeed();
		
		TwitchPostsContainer GetPosts(const std::wstring& channel_name, size_t count = 0) const;
		TwitchPost GetPost(const std::wstring& channel_name, size_t id) const; //TODO: size_t is not quite right. May be will had to change to string type
		TwitchPost Post(const std::wstring& channel_name, const std::wstring& body, bool share = false) const;
		bool DeletePost(const std::wstring& channel_name, size_t id) const; //TODO: size_t -> string?
		bool AddReaction(const std::wstring& channel_name, size_t id, size_t emote_id) const;
		bool RemoveReaction(const std::wstring& channel_name, size_t id, size_t emote_id) const;



	};

	template <> TwitchPost Create<TwitchPost>(const web::json::value& value);

}
