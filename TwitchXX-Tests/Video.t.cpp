//
// Created by buran on 17/03/18.
//

#include <gtest/gtest.h>
#include <Api.h>
#include <Video.h>
#include <TestConstants.h>
#include "TestUtils.h"

class VideoTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api{TestUtils::initOptionsFromConfig()};
};


TEST_F(VideoTest, byUserId)
{
    auto [result, cursor] = TwitchXX::getVideos(_api, {}, phoenix_id);
    EXPECT_GT(result.size(), 1);
    EXPECT_GT(cursor.size(),5);
    for(const auto& v: result)
    {
        EXPECT_EQ(v.UserId,phoenix_id);
    }
}

TEST_F(VideoTest, byGameId)
{
    auto [result, cursor] = TwitchXX::getVideos(_api, {}, 0, 29595);
    EXPECT_EQ(result.size(),20);
    EXPECT_GT(cursor.size(),5);
}
