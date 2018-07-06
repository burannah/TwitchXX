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
