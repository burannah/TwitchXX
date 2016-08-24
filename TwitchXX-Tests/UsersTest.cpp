#include "UsersTest.h"


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