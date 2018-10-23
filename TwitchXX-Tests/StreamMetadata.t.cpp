//
// Created by buran on 28/02/18.
//

#include <gtest/gtest.h>
#include <StreamMetadata.h>
#include <Api.h>
#include "TestUtils.h"

const unsigned long long OVERWATCH_ID=488552;
const unsigned long long HEARTHSTONE_ID=138585;

class StreamMetadataTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api{TestUtils::initOptionsFromConfig()};
    TwitchXX::StreamsOptions _opt;
};


TEST_F(StreamMetadataTest, getTop10)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getStreamsMetadata(_api, 10);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_EQ(streams.size(),10);
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, getNex10)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getStreamsMetadata(_api, 10);
                auto cursor = std::get<1>(result);
                result = TwitchXX::getStreamsMetadata(_api, 10, nullptr, cursor.c_str());
                auto streams = std::get<0>(result);
                EXPECT_EQ(streams.size(),10);
            });
}


TEST_F(StreamMetadataTest, getByGameId)
{
    _opt.first = 20;
    _opt.gameIds = {OVERWATCH_ID, HEARTHSTONE_ID};
    _opt.type = TwitchXX::StreamType::Value::ALL;

    auto result = TwitchXX::getStreamsMetadata(_api, _opt);
    auto streams = std::get<0>(result);
    auto cursor = std::get<1>(result);
    EXPECT_EQ(streams.size(),_opt.first);
    for(const auto& stream: streams)
    {
        EXPECT_TRUE(stream.GameId == OVERWATCH_ID || stream.GameId == HEARTHSTONE_ID);
    }
    EXPECT_GE(cursor.size(),5);
}

TEST_F(StreamMetadataTest, getByCommunityId)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;
                _opt.type = ::TwitchXX::StreamType::Value::ALL;
                _opt.communitIds.emplace_back("2caef3bd-b3db-4eed-a748-f3ee124b33aa");

                auto result = TwitchXX::getStreamsMetadata(_api, _opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(streams.size(),0);
                EXPECT_LE(streams.size(),_opt.first);
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, getByLang)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;
                _opt.type = ::TwitchXX::StreamType::Value::ALL;
                _opt.langs.emplace_back("ru");

                auto result = TwitchXX::getStreamsMetadata(_api, _opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(streams.size(),0);
                EXPECT_LE(streams.size(),_opt.first);
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, getByType)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;
                _opt.type = ::TwitchXX::StreamType::Value::LIVE;

                auto result = TwitchXX::getStreamsMetadata(_api, _opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(streams.size(),0);
                EXPECT_LE(streams.size(),_opt.first);
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, getByUserId)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;
                _opt.type = ::TwitchXX::StreamType::Value::ALL;
                _opt.userIds.emplace_back(51977856);

                auto result = TwitchXX::getStreamsMetadata(_api, _opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GE(streams.size(),0);
                EXPECT_LE(streams.size(),_opt.first);
                for(const auto& stream: streams)
                {
                    EXPECT_EQ(stream.UserId, _opt.userIds[0]);
                }
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, limits)
{
    _opt.first = 20;

    TwitchXX::StreamMetadata::RateLimits limits;

    auto result = TwitchXX::getStreamsMetadata(_api, _opt, &limits);
    auto streams = std::get<0>(result);
    auto cursor = std::get<1>(result);
    EXPECT_GT(limits.Limit, limits.Remaining);
    EXPECT_GT(limits.Limit, 0);
    EXPECT_GT(limits.Remaining, 0);
}

