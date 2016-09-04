#include "UsersTest.h"
#include <TwitchException.h>
#include <bitset>


TEST_F(UsersTest, GetBlocked)
{
	TwitchXX::TwitchBlockedUsersContainer banned;

	ASSERT_NO_THROW(
	{
		banned = _api->GetBlockedUsers(_channel_name);
	});

	EXPECT_EQ(banned.size(), 2U);
	auto ban = banned.begin();
	EXPECT_EQ(ban->User.Name.Get(), U("k9rewards"));
	ban = std::next(ban);
	EXPECT_EQ(ban->User.Name.Get(), U("adffjftuyjrthtrh"));
}

TEST_F(UsersTest, BlockUnblock)
{
	TwitchXX::TwitchBlockedUsersContainer banned;

	auto first_name = U("test_user1");
	TwitchXX::TwitchBlockedUser new_ban;
	ASSERT_NO_THROW(
	{
		new_ban = _api->BlockUser(_channel_name,first_name);
	});

	EXPECT_EQ(new_ban.User.Name.Get(), first_name);
	banned = _api->GetBlockedUsers(_channel_name);
	auto it = std::find_if(banned.begin(), banned.end(), [&](const TwitchXX::TwitchBlockedUser& e) {return e.User.Name.Get() == first_name; });
	ASSERT_TRUE(it != banned.end());

	ASSERT_NO_THROW(
	{
		EXPECT_TRUE(_api->UnblockUser(_channel_name,first_name));
	});

	banned = _api->GetBlockedUsers(_channel_name);
	it = std::find_if(banned.begin(), banned.end(), [&](const TwitchXX::TwitchBlockedUser& e) {return e.User.Name.Get() == first_name; });
	ASSERT_TRUE(it == banned.end());
}


TEST_F(UsersTest,GetFollowedChannels)
{
	TwitchXX::TwitchFollowedChannelsContainer follows;

	ASSERT_NO_THROW(
	{
		follows = _api->GetChannelsFollowedByUser(_channel_name);
	});

	EXPECT_EQ(follows.size(), 34);
}

TEST_F(UsersTest, GetFollowedChannel)
{
	TwitchXX::TwitchFollowedChannel follow;
	ASSERT_NO_THROW(
	{
		follow = _api->GetFollowingChannel(_channel_name,L"starladder1");
	});

	EXPECT_EQ(follow.Channel.Name.Get(), L"starladder1");
	EXPECT_FALSE(follow.Notifications.Get());
}

TEST_F(UsersTest, FollowUnfollowChannel)
{
	TwitchXX::TwitchFollowedChannel follow;

	ASSERT_THROW(
	{
		follow = _api->GetFollowingChannel(_channel_name,L"test_channel");
	}, TwitchXX::TwitchException);

	ASSERT_NO_THROW(
	{
		follow = _api->FollowChannel(_channel_name,L"test_channel",true);
	});

	EXPECT_EQ(follow.Channel.Name.Get(), L"test_channel");
	EXPECT_TRUE(follow.Notifications.Get());

	ASSERT_NO_THROW(
	{
		_api->UnfollowChannel(_channel_name,L"test_channel");
	});
}

TEST_F(UsersTest, GetCurrentUserStatus)
{
	TwitchXX::AuthToken status;
	ASSERT_NO_THROW(
	{
		status = _api->GetCurrentUserStatus();
	});

	EXPECT_EQ(status.Name.Get(), U("burannah"));
	using T = std::underlying_type_t<TwitchXX::AuthScope>;
	auto token_scopes = status.AuthorizationScopes.Get();
	for(const auto& scope : TwitchXX::TwitchUsers::Scopes)
	{
		auto has_flag = token_scopes & scope.first;
		if(!has_flag)
		{
			std::wcout << L"Has no flag " << scope.second << "\n";
		}
		EXPECT_TRUE(has_flag);
	}
}

TEST_F(UsersTest, GetUserSubscribedChannel)
{
	TwitchXX::TwitchFollowedChannel result;

	ASSERT_NO_THROW(
	{
		result = _api->GetUserSubscribedChannel(U("starladder1"),_channel_name);
	});

	EXPECT_EQ(result.Channel.Name.Get(), U("starladder1"));
}