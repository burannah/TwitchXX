//
// Created by buran on 12/03/18.
//

#include <gtest/gtest.h>
#include <Api.h>
#include <UserFollows.h>

class UserFollowsTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api;
};

TEST_F(UserFollowsTest, to)
{
    TwitchXX::UserFollowsOptions opt;
    opt.to = "51977856"; //Buran
    auto [users, total, cursor] = TwitchXX::getUserFollows(_api, opt);
    EXPECT_EQ(users.size(),2);
    EXPECT_EQ(total, 2);
    EXPECT_GT(cursor.size(), 5);
}

TEST_F(UserFollowsTest, from)
{
    TwitchXX::UserFollowsOptions opt;
    opt.from = "716049"; //Alkali
    auto [users, total, cursor] = TwitchXX::getUserFollows(_api, opt);
    EXPECT_EQ(users.size(),1);
    EXPECT_EQ(total, 1);
    EXPECT_GT(cursor.size(), 5);
}

