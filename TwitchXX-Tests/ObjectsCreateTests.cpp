#include <gtest/gtest.h>
#include <cpprest/json.h>
#include <TwitchGames.h>
#include <TwitchStream.h>
#include <TwitchStreams.h>
#include <TwitchChannels.h>
#include <TwitchChannelFeed.h>
#include <TwitchChat.h>
#include <TwitchUsers.h>

TEST(Create, Game)
{
	auto s = U("{\
				\"game\": {\
				\"name\": \"Counter-Strike: Global Offensive\",\
				\"box\" : {\
						\"large\": \"http://static-cdn.jtvnw.net/ttv-boxart/Counter-Strike:%20Global%20Offensive-272x380.jpg\",\
						\"medium\" : \"http://static-cdn.jtvnw.net/ttv-boxart/Counter-Strike:%20Global%20Offensive-136x190.jpg\",\
						\"small\" : \"http://static-cdn.jtvnw.net/ttv-boxart/Counter-Strike:%20Global%20Offensive-52x72.jpg\",\
						\"template\" : \"http://static-cdn.jtvnw.net/ttv-boxart/Counter-Strike:%20Global%20Offensive-{width}x{height}.jpg\"\
				},\
				\"logo\": {\
						\"large\": \"http://static-cdn.jtvnw.net/ttv-logoart/Counter-Strike:%20Global%20Offensive-240x144.jpg\",\
						\"medium\" : \"http://static-cdn.jtvnw.net/ttv-logoart/Counter-Strike:%20Global%20Offensive-120x72.jpg\",\
						\"small\" : \"http://static-cdn.jtvnw.net/ttv-logoart/Counter-Strike:%20Global%20Offensive-60x36.jpg\",\
						\"template\" : \"http://static-cdn.jtvnw.net/ttv-logoart/Counter-Strike:%20Global%20Offensive-{width}x{height}.jpg\"\
				},\
				\"_links\": {},\
				\"_id\" : 32399,\
				\"giantbomb_id\" : 36113\
			},\
			\"viewers\": 23873,\
			\"channels\" : 305\
		}");
	TwitchXX::TwitchGame game;
	web::json::value v;
	std::wstringstream ss(s);
	ss >> v;
	EXPECT_NO_THROW(
	{
		game = TwitchXX::Create<TwitchXX::TwitchGame>(v);
	}
	);
	EXPECT_EQ(game.Name.Get(), U("Counter-Strike: Global Offensive"));
	EXPECT_EQ(game.Id, unsigned{ 32399 });
	EXPECT_EQ(game.Giantbomb_Id, unsigned{ 36113 });
	EXPECT_EQ(game.Channels, unsigned{ 305 });
	EXPECT_EQ(game.Viewers, unsigned{ 23873 });
	EXPECT_EQ(game.Box.size(), unsigned{ 4 });
	EXPECT_EQ(game.Logo.size(), unsigned{ 4 });
	for (const auto& box : game.Box)
	{
		EXPECT_GT(box.first.length(), unsigned{ 1 });
		EXPECT_GT(box.second.length(), unsigned{ 1 });
	}

	for (const auto& logo : game.Logo)
	{
		EXPECT_GT(logo.first.length(), unsigned{ 1 });
		EXPECT_GT(logo.second.length(), unsigned{ 1 });
	}

}

TEST(Create, StreamOffline)
{
	auto s = U("{\
		\"stream\": null,\
		\"_links\" : {\
		\"self\": \"https://api.twitch.tv/kraken/streams/test_channel\",\
			\"channel\" : \"https://api.twitch.tv/kraken/channels/test_channel\"\
	}\
	}");

	TwitchXX::TwitchStream stream;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		stream = TwitchXX::Create<TwitchXX::TwitchStream>(v[U("stream")]);
	});

	EXPECT_TRUE(stream.Offline);
}
TEST(Create, StreamOnline)
{
	auto s = U(
		"{\
		\"_links\": {\
			\"channel\": \"https://api.twitch.tv/kraken/channels/test_channel\",\
			\"self\" : \"https://api.twitch.tv/kraken/streams/test_channel\"\
		},\
		\"stream\" : {\
			\"game\": \"StarCraft II: Heart of the Swarm\",\
			\"viewers\" : 2123,\
			\"average_fps\" : 29.9880749574,\
			\"delay\" : 0,\
			\"video_height\" : 720,\
			\"is_playlist\" : false,\
			\"created_at\" : \"2015-02-12T04:42:31Z\",\
			\"_id\" : 4989654544,\
			\"channel\" : {\
				\"mature\": false,\
				\"status\" : \"test status\",\
				\"broadcaster_language\" : \"en\",\
				\"display_name\" : \"test_channel\",\
				\"game\" : \"StarCraft II: Heart of the Swarm\",\
				\"delay\" : null,\
				\"language\" : \"en\",\
				\"_id\" : 12345,\
				\"name\" : \"test_channel\",\
				\"created_at\" : \"2007-05-22T10:39:54Z\",\
				\"updated_at\" : \"2015-02-12T04:15:49Z\",\
				\"logo\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_image-94a42b3a13c31c02-300x300.jpeg\",\
				\"banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_header_image-08dd874c17f39837-640x125.png\",\
				\"video_banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_offline_image-b314c834d210dc1a-640x360.png\",\
				\"background\" : null,\
				\"profile_banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_banner-6936c61353e4aeed-480.png\",\
				\"profile_banner_background_color\" : null,\
				\"partner\" : true,\
				\"url\" : \"http://www.twitch.tv/test_channel\",\
				\"views\" : 49144894,\
				\"followers\" : 215780,\
				\"_links\" : {\
					\"self\": \"https://api.twitch.tv/kraken/channels/test_channel\",\
					\"follows\" : \"https://api.twitch.tv/kraken/channels/test_channel/follows\",\
					\"commercial\" : \"https://api.twitch.tv/kraken/channels/test_channel/commercial\",\
					\"stream_key\" : \"https://api.twitch.tv/kraken/channels/test_channel/stream_key\",\
					\"chat\" : \"https://api.twitch.tv/kraken/chat/test_channel\",\
					\"features\" : \"https://api.twitch.tv/kraken/channels/test_channel/features\",\
					\"subscriptions\" : \"https://api.twitch.tv/kraken/channels/test_channel/subscriptions\",\
					\"editors\" : \"https://api.twitch.tv/kraken/channels/test_channel/editors\",\
					\"teams\" : \"https://api.twitch.tv/kraken/channels/test_channel/teams\",\
					\"videos\" : \"https://api.twitch.tv/kraken/channels/test_channel/videos\"\
				}\
			},\
			\"preview\": {\
				\"small\": \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-80x45.jpg\",\
				\"medium\" : \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-320x180.jpg\",\
				\"large\" : \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-640x360.jpg\",\
				\"template\" : \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-{width}x{height}.jpg\"\
			},\
			\"_links\": {\
				\"self\": \"https://api.twitch.tv/kraken/streams/test_channel\"\
			}\
		}\
	}");

	TwitchXX::TwitchStream stream;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		stream = TwitchXX::Create<TwitchXX::TwitchStream>(v[U("stream")]);
	});

	EXPECT_EQ(stream.Game.Get(),U("StarCraft II: Heart of the Swarm"));
	EXPECT_EQ(stream.Viewers, unsigned{ 2123 });
	EXPECT_EQ(stream.Avg_Fps.Get(), double{ 29.9880749574 });
	EXPECT_EQ(stream.Delay, unsigned{ 0 });
	EXPECT_EQ(stream.Video_Height, unsigned{ 720 });
	EXPECT_FALSE(stream.Is_Playlist);
	EXPECT_EQ(stream.Created.to_string(), U("2015-02-12T04:42:31Z"));
	EXPECT_EQ(stream.Id, 4989654544);
	EXPECT_EQ(stream.Preview.size(), unsigned{ 4 });
	for (const auto& preview : stream.Preview)
	{
		EXPECT_GT(preview.first.length(), unsigned{ 1 });
		EXPECT_GT(preview.second.length(), unsigned{ 1 });
	}

	auto channel = stream.Channel;
	EXPECT_FALSE(channel.Mature);
	EXPECT_EQ(channel.Status.Get(), U("test status"));
	EXPECT_EQ(channel.Broadcaster_Language.Get(), U("en"));
	EXPECT_EQ(channel.Display_Name.Get(), U("test_channel"));
	EXPECT_EQ(channel.Game.Get(), stream.Game.Get());
	EXPECT_EQ(channel.Game.Get(), U("StarCraft II: Heart of the Swarm"));
	EXPECT_EQ(channel.Delay, 0);
	EXPECT_EQ(channel.Language.Get(), U("en"));
	EXPECT_EQ(channel.Id, 12345);
	EXPECT_EQ(channel.Name.Get(), U("test_channel"));
	EXPECT_EQ(channel.Created.Get(), TwitchXX::DateFromString(U("2007-05-22T10:39:54Z")));
	EXPECT_EQ(channel.Created.to_string(), U("2007-05-22T10:39:54Z"));
	EXPECT_EQ(channel.Updated.to_string(), U("2015-02-12T04:15:49Z"));
	EXPECT_EQ(channel.Logo.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_image-94a42b3a13c31c02-300x300.jpeg"));
	EXPECT_EQ(channel.Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_header_image-08dd874c17f39837-640x125.png"));
	EXPECT_EQ(channel.Video_Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_offline_image-b314c834d210dc1a-640x360.png"));
	EXPECT_EQ(channel.Background.Get(), U(""));
	EXPECT_EQ(channel.Profile_Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_banner-6936c61353e4aeed-480.png"));
	EXPECT_EQ(channel.Profile_Banner_Background_Color.Get(), U(""));
	EXPECT_TRUE(channel.Partner);
	EXPECT_EQ(channel.Url.Get(), U("http://www.twitch.tv/test_channel"));
	EXPECT_EQ(channel.Views, unsigned{ 49144894 });
	EXPECT_EQ(channel.Followers, unsigned{ 215780 });
}

TEST(Create,FeaturedStream)
{
	auto s = U("{\
		\"image\": \"http://s.jtvnw.net/jtv_user_pictures/hosted_images/TwitchPartnerSpotlight.png\",\
		\"text\" : \"<p>some html to describe this featured stream</p>\",\
		\"title\" : \"Twitch Partner Spotlight\",\
		\"sponsored\" : false,\
		\"scheduled\" : true,\
		\"stream\" : {\
		\"game\": \"StarCraft II: Heart of the Swarm\",\
			\"viewers\" : 2123,\
			\"average_fps\" : 29.9880749574,\
			\"delay\" : 0,\
			\"video_height\" : 720,\
			\"created_at\" : \"2015-02-12T04:42:31Z\",\
			\"_id\" : 4989654544,\
			\"channel\" : {\
			\"mature\": false,\
				\"status\" : \"test status\",\
				\"broadcaster_language\" : \"en\",\
				\"display_name\" : \"test_channel\",\
				\"game\" : \"StarCraft II: Heart of the Swarm\",\
				\"delay\" : null,\
				\"language\" : \"en\",\
				\"_id\" : 12345,\
				\"name\" : \"test_channel\",\
				\"created_at\" : \"2007-05-22T10:39:54Z\",\
				\"updated_at\" : \"2015-02-12T04:15:49Z\",\
				\"logo\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_image-94a42b3a13c31c02-300x300.jpeg\",\
				\"banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_header_image-08dd874c17f39837-640x125.png\",\
				\"video_banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_offline_image-b314c834d210dc1a-640x360.png\",\
				\"background\" : null,\
				\"profile_banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_banner-6936c61353e4aeed-480.png\",\
				\"profile_banner_background_color\" : null,\
				\"partner\" : true,\
				\"url\" : \"http://www.twitch.tv/test_channel\",\
				\"views\" : 49144894,\
				\"followers\" : 215780,\
				\"_links\" : {\
				\"self\": \"https://api.twitch.tv/kraken/channels/test_channel\",\
					\"follows\" : \"https://api.twitch.tv/kraken/channels/test_channel/follows\",\
					\"commercial\" : \"https://api.twitch.tv/kraken/channels/test_channel/commercial\",\
					\"stream_key\" : \"https://api.twitch.tv/kraken/channels/test_channel/stream_key\",\
					\"chat\" : \"https://api.twitch.tv/kraken/chat/test_channel\",\
					\"features\" : \"https://api.twitch.tv/kraken/channels/test_channel/features\",\
					\"subscriptions\" : \"https://api.twitch.tv/kraken/channels/test_channel/subscriptions\",\
					\"editors\" : \"https://api.twitch.tv/kraken/channels/test_channel/editors\",\
					\"teams\" : \"https://api.twitch.tv/kraken/channels/test_channel/teams\",\
					\"videos\" : \"https://api.twitch.tv/kraken/channels/test_channel/videos\"\
			}\
		},\
			\"preview\": {\
			\"small\": \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-80x45.jpg\",\
				\"medium\" : \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-320x180.jpg\",\
				\"large\" : \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-640x360.jpg\",\
				\"template\" : \"http://static-cdn.jtvnw.net/previews-ttv/live_user_test_channel-{width}x{height}.jpg\"\
		},\
			\"_links\": {\
				\"self\": \"https://api.twitch.tv/kraken/streams/test_channel\"\
			}\
	}\
}");

	TwitchXX::TwitchFeaturedStream featured_stream;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		featured_stream = TwitchXX::Create<TwitchXX::TwitchFeaturedStream>(v);
	});
	EXPECT_EQ(featured_stream.Image.Get(), U("http://s.jtvnw.net/jtv_user_pictures/hosted_images/TwitchPartnerSpotlight.png"));
	EXPECT_EQ(featured_stream.Text.Get(), U("<p>some html to describe this featured stream</p>"));
	EXPECT_FALSE(featured_stream.Sponsored);
	EXPECT_TRUE(featured_stream.Scheduled);

	auto stream = featured_stream.Stream;
	EXPECT_EQ(stream.Game.Get(), U("StarCraft II: Heart of the Swarm"));
	EXPECT_EQ(stream.Viewers, unsigned{ 2123 });
	EXPECT_EQ(stream.Avg_Fps.Get(), 29.9880749574);
	EXPECT_EQ(stream.Delay, unsigned{ 0 });
	EXPECT_EQ(stream.Video_Height, unsigned{ 720 });
	EXPECT_FALSE(stream.Is_Playlist);
	EXPECT_EQ(stream.Created.to_string(), U("2015-02-12T04:42:31Z"));
	EXPECT_EQ(stream.Id, 4989654544);
	EXPECT_EQ(stream.Preview.size(), unsigned{ 4 });
	for (const auto& preview : stream.Preview)
	{
		EXPECT_GT(preview.first.length(), unsigned{ 1 });
		EXPECT_GT(preview.second.length(), unsigned{ 1 });
	}

	auto channel = stream.Channel;
	EXPECT_FALSE(channel.Mature);
	EXPECT_EQ(channel.Status.Get(), U("test status"));
	EXPECT_EQ(channel.Broadcaster_Language.Get(), U("en"));
	EXPECT_EQ(channel.Display_Name.Get(), U("test_channel"));
	EXPECT_EQ(channel.Game.Get(), stream.Game.Get());
	EXPECT_EQ(channel.Game.Get(), U("StarCraft II: Heart of the Swarm"));
	EXPECT_EQ(channel.Delay, 0);
	EXPECT_EQ(channel.Language.Get(), U("en"));
	EXPECT_EQ(channel.Id, 12345);
	EXPECT_EQ(channel.Name.Get(), U("test_channel"));
	EXPECT_EQ(channel.Created.Get(), TwitchXX::DateFromString(U("2007-05-22T10:39:54Z")));
	EXPECT_EQ(channel.Created.to_string(), U("2007-05-22T10:39:54Z"));
	EXPECT_EQ(channel.Updated.to_string(), U("2015-02-12T04:15:49Z"));
	EXPECT_EQ(channel.Logo.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_image-94a42b3a13c31c02-300x300.jpeg"));
	EXPECT_EQ(channel.Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_header_image-08dd874c17f39837-640x125.png"));
	EXPECT_EQ(channel.Video_Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_offline_image-b314c834d210dc1a-640x360.png"));
	EXPECT_EQ(channel.Background.Get(), U(""));
	EXPECT_EQ(channel.Profile_Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_banner-6936c61353e4aeed-480.png"));
	EXPECT_EQ(channel.Profile_Banner_Background_Color.Get(), U(""));
	EXPECT_TRUE(channel.Partner);
	EXPECT_EQ(channel.Url.Get(), U("http://www.twitch.tv/test_channel"));
	EXPECT_EQ(channel.Views, unsigned{ 49144894 });
	EXPECT_EQ(channel.Followers, unsigned{ 215780 });
}

TEST(Create,Channel)
{
	auto s = U("{\
		\"mature\": false,\
		\"status\" : \"test status\",\
		\"broadcaster_language\" : \"en\",\
		\"display_name\" : \"test_channel\",\
		\"game\" : \"Gaming Talk Shows\",\
		\"delay\" : null,\
		\"language\" : \"en\",\
		\"_id\" : 12345,\
		\"name\" : \"test_channel\",\
		\"created_at\" : \"2007-05-22T10:39:54Z\",\
		\"updated_at\" : \"2015-02-12T04:15:49Z\",\
		\"logo\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_image-94a42b3a13c31c02-300x300.jpeg\",\
		\"banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_header_image-08dd874c17f39837-640x125.png\",\
		\"video_banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_offline_image-b314c834d210dc1a-640x360.png\",\
		\"background\" : null,\
		\"profile_banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_banner-6936c61353e4aeed-480.png\",\
		\"profile_banner_background_color\" : null,\
		\"partner\" : true,\
		\"url\" : \"http://www.twitch.tv/test_channel\",\
		\"views\" : 49144894,\
		\"followers\" : 215780,\
		\"_links\" : {\
		\"self\": \"https://api.twitch.tv/kraken/channels/test_channel\",\
			\"follows\" : \"https://api.twitch.tv/kraken/channels/test_channel/follows\",\
			\"commercial\" : \"https://api.twitch.tv/kraken/channels/test_channel/commercial\",\
			\"stream_key\" : \"https://api.twitch.tv/kraken/channels/test_channel/stream_key\",\
			\"chat\" : \"https://api.twitch.tv/kraken/chat/test_channel\",\
			\"features\" : \"https://api.twitch.tv/kraken/channels/test_channel/features\",\
			\"subscriptions\" : \"https://api.twitch.tv/kraken/channels/test_channel/subscriptions\",\
			\"editors\" : \"https://api.twitch.tv/kraken/channels/test_channel/editors\",\
			\"teams\" : \"https://api.twitch.tv/kraken/channels/test_channel/teams\",\
			\"videos\" : \"https://api.twitch.tv/kraken/channels/test_channel/videos\"\
	}\
}");
	TwitchXX::TwitchChannel channel;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		channel = TwitchXX::Create<TwitchXX::TwitchChannel>(v);
	});

	EXPECT_FALSE(channel.Mature);
	EXPECT_EQ(channel.Status.Get(), U("test status"));
	EXPECT_EQ(channel.Broadcaster_Language.Get(), U("en"));
	EXPECT_EQ(channel.Display_Name.Get(), U("test_channel"));
	EXPECT_EQ(channel.Game.Get(), U("Gaming Talk Shows"));
	EXPECT_EQ(channel.Delay, 0);
	EXPECT_EQ(channel.Language.Get(), U("en"));
	EXPECT_EQ(channel.Id, 12345);
	EXPECT_EQ(channel.Name.Get(), U("test_channel"));
	EXPECT_EQ(channel.Created.Get(), TwitchXX::DateFromString(U("2007-05-22T10:39:54Z")));
	EXPECT_EQ(channel.Created.to_string(), U("2007-05-22T10:39:54Z"));
	EXPECT_EQ(channel.Updated.to_string(), U("2015-02-12T04:15:49Z"));
	EXPECT_EQ(channel.Logo.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_image-94a42b3a13c31c02-300x300.jpeg"));
	EXPECT_EQ(channel.Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_header_image-08dd874c17f39837-640x125.png"));
	EXPECT_EQ(channel.Video_Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-channel_offline_image-b314c834d210dc1a-640x360.png"));
	EXPECT_EQ(channel.Background.Get(), U(""));
	EXPECT_EQ(channel.Profile_Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/test_channel-profile_banner-6936c61353e4aeed-480.png"));
	EXPECT_EQ(channel.Profile_Banner_Background_Color.Get(), U(""));
	EXPECT_TRUE(channel.Partner);
	EXPECT_EQ(channel.Url.Get(), U("http://www.twitch.tv/test_channel"));
	EXPECT_EQ(channel.Views, unsigned{ 49144894 });
	EXPECT_EQ(channel.Followers, unsigned{ 215780 });
}

TEST(Create,User)
{
	auto s = U("{\
		\"display_name\" : \"bangbangalang\",\
		\"_id\": 104447238,\
		\"name\" : \"bangbangalang\",\
		\"type\" : \"user\",\
		\"bio\" : \"i like turtles and cats\",\
		\"created_at\" : \"2015-10-15T19:52:17Z\",\
		\"updated_at\" : \"2016-01-29T21:06:42Z\",\
		\"logo\" : null,\
		\"_links\" : {\
			\"self\": \"https://api.twitch.tv/kraken/users/bangbangalang\"\
		}\
		}");

	TwitchXX::TwitchUser user;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		user = TwitchXX::Create<TwitchXX::TwitchUser>(v);
	});

	EXPECT_EQ(user.Id, 104447238);
	EXPECT_EQ(user.Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Type.Get(), U("user"));
	EXPECT_EQ(user.Bio.Get(), U("i like turtles and cats"));
	EXPECT_EQ(user.Created.Get(), TwitchXX::DateFromString(U("2015-10-15T19:52:17Z")));
	EXPECT_EQ(user.Created.to_string(), U("2015-10-15T19:52:17Z"));
	EXPECT_EQ(user.Updated.Get(), TwitchXX::DateFromString(U("2016-01-29T21:06:42Z")));
	EXPECT_EQ(user.Updated.to_string(), U("2016-01-29T21:06:42Z"));
	EXPECT_EQ(user.Logo.Get(), U(""));

}

TEST(Create,Team)
{
	auto s = U("{\
		\"_links\": {\
		\"self\": \"https://api.twitch.tv/kraken/teams/staff\"\
	},\
		\"_id\" : 10,\
			\"name\" : \"staff\",\
			\"info\" : \"We save the world..\\n\\n\\n\",\
			\"display_name\" : \"Twitch Staff\",\
			\"created_at\" : \"2011-10-25T23:55:47Z\",\
			\"updated_at\" : \"2013-05-24T00:17:12Z\",\
			\"logo\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/team-staff-team_logo_image-e26f89ac4f424216-300x300.png\",\
			\"banner\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/team-staff-banner_image-c81e25b281c06e8f-640x125.png\",\
			\"background\" : null\
}");
	TwitchXX::TwitchTeam team;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		team = TwitchXX::Create<TwitchXX::TwitchTeam>(v);
	});

	EXPECT_EQ(team.Id, 10);
	EXPECT_EQ(team.Name.Get(), U("staff"));
	EXPECT_EQ(team.Info.Get(), U("We save the world..\n\n\n"));
	EXPECT_EQ(team.Display_Name.Get(), U("Twitch Staff"));
	EXPECT_EQ(team.Created.Get(), TwitchXX::DateFromString(U("2011-10-25T23:55:47Z")));
	EXPECT_EQ(team.Created.to_string(), U("2011-10-25T23:55:47Z"));
	EXPECT_EQ(team.Updated.Get(), TwitchXX::DateFromString(U("2013-05-24T00:17:12Z")));
	EXPECT_EQ(team.Updated.to_string(), U("2013-05-24T00:17:12Z"));
	EXPECT_EQ(team.Logo.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/team-staff-team_logo_image-e26f89ac4f424216-300x300.png"));
	EXPECT_EQ(team.Banner.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/team-staff-banner_image-c81e25b281c06e8f-640x125.png"));
	EXPECT_EQ(team.Background.Get(), U(""));
}

TEST(Create,TwitchPost)
{
	auto s = U("{\
		\"id\": \"20\",\
		\"created_at\" : \"2016-01-29T21:07:23.075611Z\",\
		\"deleted\" : false,\
		\"emotes\" : [],\
		\"reactions\" : {\
		\"endorse\": {\
			\"count\": 2,\
				\"user_ids\" : []\
		}\
	},\
		\"body\": \"Kappa post\",\
		\"user\" : {\
		\"display_name\": \"bangbangalang\",\
			\"_id\" : 104447238,\
			\"name\" : \"bangbangalang\",\
			\"type\" : \"user\",\
			\"bio\" : \"i like turtles and cats\",\
			\"created_at\" : \"2015-10-15T19:52:17Z\",\
			\"updated_at\" : \"2016-01-29T21:06:42Z\",\
			\"logo\" : null,\
			\"_links\" : {\
			\"self\": \"https://api.twitch.tv/kraken/users/bangbangalang\"\
		}\
	}\
}");
	TwitchXX::TwitchPost post;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		post = TwitchXX::Create<TwitchXX::TwitchPost>(v);
	});

	EXPECT_EQ(post.Id, 20);
	EXPECT_EQ(post.Created.Get(), TwitchXX::DateFromString(U("2016-01-29T21:07:23.075611Z")));
	EXPECT_EQ(post.Created.to_string(), U("2016-01-29T21:07:23Z"));
	EXPECT_FALSE(post.Deleted);
	EXPECT_EQ(post.Endorsed_Count, 2);
	EXPECT_EQ(post.Endorsed_Users.size(), 0);
	EXPECT_EQ(post.Body.Get(), U("Kappa post"));

	auto user = post.Author;
	EXPECT_EQ(user.Id, 104447238);
	EXPECT_EQ(user.Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Type.Get(), U("user"));
	EXPECT_EQ(user.Bio.Get(), U("i like turtles and cats"));
	EXPECT_EQ(user.Created.Get(), TwitchXX::DateFromString(U("2015-10-15T19:52:17Z")));
	EXPECT_EQ(user.Created.to_string(), U("2015-10-15T19:52:17Z"));
	EXPECT_EQ(user.Updated.Get(), TwitchXX::DateFromString(U("2016-01-29T21:06:42Z")));
	EXPECT_EQ(user.Updated.to_string(), U("2016-01-29T21:06:42Z"));
	EXPECT_EQ(user.Logo.Get(), U(""));

}

TEST(Create, TwitchEmoticon)
{
	auto s = U(" {\
		\"regex\": \"\\:-?\\(\",\
		\"images\" : [\
	{\
		\"emoticon_set\": null,\
			\"height\" : 18,\
			\"width\" : 24,\
			\"url\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/chansub-global-emoticon-d570c4b3b8d8fc4d-24x18.png\"\
	},\
	{\
		\"emoticon_set\": 33,\
		\"height\" : 18,\
		\"width\" : 21,\
		\"url\" : \"http://static-cdn.jtvnw.net/jtv_user_pictures/chansub-global-emoticon-c41c5c6c88f481cd-21x18.png\"\
	}\
		]\
}");
	TwitchXX::TwitchEmoticon emote;
	std::wstringstream ss(s);
	web::json::value v;
	ss >> v;

	EXPECT_NO_THROW(
	{
		emote = TwitchXX::Create<TwitchXX::TwitchEmoticon>(v);
	});

	EXPECT_EQ(emote.Regex.Get(), U("\\:-?\\(")); //TODO: Fails but looks like it's JSON parsing error. Postponed
	auto images = emote.Images;
	EXPECT_EQ(images.size(), 2);
	auto it = images.begin();
	EXPECT_EQ(it->Set_Id, 0);
	EXPECT_EQ(it->Height, 18);
	EXPECT_EQ(it->Width, 24);
	EXPECT_EQ(it->Url.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/chansub-global-emoticon-d570c4b3b8d8fc4d-24x18.png"));
	it = std::next(it);
	EXPECT_EQ(it->Set_Id, 33);
	EXPECT_EQ(it->Height, 18);
	EXPECT_EQ(it->Width, 21);
	EXPECT_EQ(it->Url.Get(), U("http://static-cdn.jtvnw.net/jtv_user_pictures/chansub-global-emoticon-c41c5c6c88f481cd-21x18.png"));
}