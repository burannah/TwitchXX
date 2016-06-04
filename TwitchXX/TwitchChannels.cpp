#include "TwitchChannels.h"
#include "JsonWrapper.h"


TwitchXX::TwitchChannels::TwitchChannels()
{
	_root_node = U("channels");
}

TwitchXX::TwitchChannels::~TwitchChannels()
{
}
template<>
TwitchXX::TwitchChannel TwitchXX::Create(const web::json::value & value)
{
	TwitchChannel channel;
	JsonWrapper wrapper(value);

	channel.Mature(wrapper[U("mature")]->as_bool());
	channel.Status(wrapper[U("status")]->as_string());
	channel.BroadcasterLanguage(wrapper[U("broadcaster_language")]->as_string());
	channel.DisplayName(wrapper[U("display_name")]->as_string());
	channel.Game(wrapper[U("game")]->as_string());
	channel.Delay(wrapper[U("delay")]->as_integer());
	channel.Language(wrapper[U("language")]->as_string());
	channel.Id(wrapper[U("_id")]->as_integer());
	channel.Name(wrapper[U("name")]->as_string());
	channel.Created(wrapper[U("created_at")]->as_string());
	channel.Updated(wrapper[U("updated_at")]->as_string());
	channel.Logo(wrapper[U("logo")]->as_string());
	channel.Banner(wrapper[U("banner")]->as_string());
	channel.VideoBanner(wrapper[U("video_banner")]->as_string());
	channel.Background(wrapper[U("background")]->as_string());
	channel.ProfileBanner(wrapper[U("profile_banner")]->as_string());
	channel.ProfileBannerBkColor(wrapper[U("profile_banner_background_color")]->as_string());
	channel.Partner(wrapper[U("partner")]->as_bool());
	channel.Url(wrapper[U("url")]->as_string());
	channel.Views(wrapper[U("views")]->as_integer());
	channel.Followers(wrapper[U("followers")]->as_integer());


	return channel;
}
