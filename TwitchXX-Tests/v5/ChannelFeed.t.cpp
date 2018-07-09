//
// Created by buran on 06/07/18.
//

#include <gtest/gtest.h>
#include <TestUtils.h>
#include <Api.h>
#include <v5/FeedPost.h>
#include <TestConstants.h>


class ChannelFeedTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api {TestUtils::initOptionsFromConfigV5()};
};


TEST_F(ChannelFeedTest, getPost)
{
    auto post = TwitchXX::v5::getPost(_api,std::to_string(buran_id),
            "0d733d5d-c192-4b78-b662-bcf3cb4e7951");

    EXPECT_EQ(post.Body, "Test");
}

TEST_F(ChannelFeedTest,getPosts)
{
    int limit = 100;
    auto [posts, cursor] = TwitchXX::v5::getPosts(_api, "44322889", limit);

    EXPECT_GE(posts.size(), 2);
    if(limit > posts.size())
    {
        EXPECT_TRUE(cursor.empty());
    }
    else
    {
        EXPECT_FALSE(cursor.empty());
    }
}


TEST_F(ChannelFeedTest, getPostsCursor)
{
    int limit = 1;
    auto [posts, cursor] = TwitchXX::v5::getPosts(_api, "44322889", limit);

    EXPECT_EQ(posts.size(), 1);
    EXPECT_FALSE(cursor.empty());

    auto [posts2, cursor2] = TwitchXX::v5::getPosts(_api, "44322889", ++limit, cursor);

    EXPECT_EQ(posts2.size(), 1);
}
