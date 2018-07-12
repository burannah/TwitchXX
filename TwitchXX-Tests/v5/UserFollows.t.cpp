//
// Created by buran on 12/07/18.
//

#include <gtest/gtest.h>
#include <Api.h>
#include <TestUtils.h>
#include <v5/UserFollows.h>
#include <TestConstants.h>


class UserFollowsv5Test : public ::testing::Test
{
protected:
    TwitchXX::Api _api {TestUtils::initOptionsFromConfigV5()};
};


TEST_F(UserFollowsv5Test, getUserFollows)
{
    auto [follows, size, cursor] = TwitchXX::v5::getChannelFollowers(_api, std::to_string(buran_id));

    EXPECT_EQ(size, 2);
    EXPECT_FALSE(cursor.empty());
    EXPECT_EQ(size, follows.size());
}

TEST_F(UserFollowsv5Test, getLazy)
{
    TwitchXX::v5::UserFollows users(_api, std::to_string(buran_id));

    EXPECT_EQ(users.at(0).User.Type, TwitchXX::UserType::Value::USER);
    EXPECT_EQ(users.at(1).User.Name, "goldagold");
}
