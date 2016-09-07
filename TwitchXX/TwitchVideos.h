#pragma once
#include "TwitchRequest.h"
#include "TwitchVideo.h"

namespace TwitchXX
{
	/// Videos are broadcasts or chapters owned by a channel. Broadcasts are unedited videos that are saved after 
	/// a streaming session. Chapters are videos edited from broadcasts by the channel's owner.
	class TwitchVideos : public TwitchRequest<TwitchVideo>
	{
	public:
		explicit TwitchVideos(const std::shared_ptr<MakeRequest>& request)
			: TwitchRequest<TwitchVideo>(request)
		{
		}
		

		///Get video by id
		///@param id video id
		///@return Twitch video object
		TwitchVideo GetVideo(unsigned long long id) const;

		///Get top videos
		///@param op set of filters for video request
		TwitchVideosContainer GetTopVideos(options& op) const;

		///A list of video objects from channels that the authenticated user is following.
		///Required scope AuthScope::USER_READ
		///Default value: limit = 10, offset = 0, broadcast_type = all
		///Broadcast types: all, archive, highlight
		///@param op set of filters for video request
		TwitchVideosContainer GetFollowedVideos(options& op) const;

	};

	template<>
	TwitchVideo Create<TwitchVideo>(const web::json::value& value);
	
}
