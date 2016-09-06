#include "TwitchVideos.h"
#include "JsonWrapper.h"
#include "TwitchChannels.h"

TwitchXX::TwitchVideo TwitchXX::TwitchVideos::GetVideo(unsigned long long id) const
{
	web::uri_builder builder(U("/videos/") + std::to_wstring(id));
	return GetSingleObject<TwitchVideo>(builder.to_uri());
}

TwitchXX::TwitchVideosContainer TwitchXX::TwitchVideos::GetTopVideos(options& op) const
{
	web::uri_builder builder(U("/videos/top"));
	auto game_it = op.find(U("game"));
	if(game_it != op.end())
	{
		builder.append_query(U("game"), *game_it);
	}
	auto period_it = op.find(U("period"));
	if(period_it != op.end())
	{
		builder.append_query(U("period"), *period_it);
	}
	auto limit_it = op.find(U("limit"));
	if(limit_it != op.end())
	{
		builder.append_query(U("limit"), *limit_it);
	}
	auto offset_it = op.find(U("offset"));
	if(offset_it != op.end())
	{
		builder.append_query(U("offset"),*offset_it);
	}

	return GetObjectsArray<TwitchVideo>(builder, U("videos"));
}

template <>
TwitchXX::TwitchVideo TwitchXX::Create<TwitchXX::TwitchVideo>(const web::json::value& value)
{
	JsonWrapper w(value);
	TwitchVideo video;

	video.Title.Set(*w[U("title")]);
	video.Description.Set(*w[U("description")]);
	video.BroadcastId.Set(*w[U("broadcast_id")]);
	video.Id.Set(*w[U("_id")]);
	video.TagList.Set(*w[U("tag_list")]);
	video.Recorded.from_string(*w[U("recorded_at")]);
	video.Game.Set(*w[U("game")]);
	video.Length.Set(*w[U("length")]);
	video.Preview.Set(*w[U("preview")]);
	video.Url.Set(*w[U("url")]);
	video.Views.Set(*w[U("views")]);
	video.BroadcastType.Set(*w[U("broadcast_type")]);
	video.Channel = Create<TwitchChannel>(value.at(U("channel")));

	return video;
}
