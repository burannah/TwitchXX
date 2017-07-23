#include "TwitchVideos.h"
#include "JsonWrapper.h"
#include "TwitchChannels.h"

TwitchXX::TwitchVideo TwitchXX::TwitchVideos::GetVideo(unsigned long long id) const
{
	web::uri_builder builder(U("/videos/") + to_ustring(id));
	return GetSingleObject<TwitchVideo>(builder.to_uri());
}

TwitchXX::TwitchVideosContainer TwitchXX::TwitchVideos::GetTopVideos(options& op) const
{
	web::uri_builder builder(U("/videos/top"));
	AddOption(builder, op, U("game"));
	AddOption(builder, op, U("period"));
	AddOption(builder, op, U("limit"));
	AddOption(builder, op, U("offset"));

	return GetObjectsArrayByNext<TwitchVideo>(builder, U("videos"));
}

TwitchXX::TwitchVideosContainer TwitchXX::TwitchVideos::GetFollowedVideos(options& op) const
{
	web::uri_builder builder(U("/videos/followed"));
	AddOption(builder, op, U("limit"));
	AddOption(builder, op, U("offset"));
	AddOption(builder, op, U("broadcast_type"));

	return GetObjectsArrayByNext<TwitchVideo>(builder,U("videos"));
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
	video.Status.Set(*w[U("status")]);
	video.TagList.Set(*w[U("tag_list")]);
	video.Recorded.from_string(*w[U("recorded_at")]);
	video.Game.Set(*w[U("game")]);
	video.Length.Set(*w[U("length")]);
	video.Preview.Set(*w[U("preview")]);
	video.Url.Set(*w[U("url")]);
	video.Views.Set(*w[U("views")]);
	video.BroadcastType.Set(*w[U("broadcast_type")]);

	JsonWrapper c(value.at(U("channel")));
	video.ChannelName.Set(*c[U("name")]);
	video.ChannelDisplayName.Set(*c[U("display_name")]);

	return video;
}
