#include "ChannelTest.h"
#include "TwitchTeam.h"

TEST_F(ChannelTest,GetChannel)
{
	TwitchXX::TwitchChannel channel;
	ASSERT_NO_THROW(
	{
		channel = _api->GetChannel(_channel_name);
	});

	EXPECT_EQ(channel.Background.Get(), U(""));
	EXPECT_EQ(channel.Banner.Get(), U(""));
	EXPECT_EQ(channel.Broadcaster_Language.Get(), U(""));
	EXPECT_EQ(channel.Created.Get(), TwitchXX::DateFromString(U("2013-11-22T19:41:35Z")));
	EXPECT_EQ(channel.Created.to_string(), U("2013-11-22T19:41:35Z"));
	EXPECT_EQ(channel.Delay, 0);
	EXPECT_EQ(channel.Display_Name.Get(), U("burannah"));
	EXPECT_EQ(channel.Followers, 1);
	EXPECT_EQ(channel.Game.Get(), U(""));
	EXPECT_EQ(channel.Language.Get(), U("ru"));
	EXPECT_EQ(channel.Id, 51977856);
}

TEST_F(ChannelTest,GetChannelEditors)
{
	TwitchXX::TwitchUsersContainer admins;
	ASSERT_NO_THROW(
	{
		admins = _api->GetChannelEditors(_channel_name);
	});

	EXPECT_EQ(admins.size(), unsigned{ 0 });

}

TEST_F(ChannelTest,UpdateChannel)
{
	TwitchXX::TwitchChannel channel;

	ASSERT_NO_THROW(
	{
		channel = _api->GetChannel(_channel_name);
	});

	auto old_title = channel.Status.Get();
	auto new_status = U("test");
	TwitchXX::options op{ {U("status"), new_status} };
	auto new_channel = _api->UpdateChannel(_channel_name,op);
	EXPECT_EQ(new_channel.Status.Get(), new_status);
	op[U("status")] = old_title;
	_api->UpdateChannel(_channel_name, op);
}

TEST_F(ChannelTest,ResetStreamKey)
{
	auto channel = _api->GetChannel(_channel_name);
	auto stream_key = channel.Stream_Key.Get();
	std::wstring new_key;
	ASSERT_NO_THROW(
	{
		new_key = _api->ResetStreamKey(_channel_name);
	});

	EXPECT_NE(stream_key, new_key);
	EXPECT_NE(new_key, U(""));
}

TEST_F(ChannelTest,StartComercial)
{
	auto b = false;

	ASSERT_NO_THROW(
	{
		b = _api->StartCommercial(_channel_name, 30);
	});

	//EXPECT_TRUE(b);
}

TEST_F(ChannelTest,GetTeams)
{
	TwitchXX::TwitchTeamsContainer teams;

	ASSERT_NO_THROW(
	{
		teams = _api->GetTeams(_channel_name);
	});

	EXPECT_EQ(teams.size(), unsigned{ 0 });
}