//
// Created by buran on 28/02/18.
//

#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <StreamMetadata.h>

const std::string OVERWATCH_ID="488552";
const std::string HEARTHSTONE_ID="138585";

class StreamMetadataTest : public ::testing::Test
{
public:
    TwitchXX::StreamsOptions _opt;
private:
    void SetUp() override;
};

void StreamMetadataTest::SetUp()
{
    Test::SetUp();

    //Init default parameters
    TwitchXX::MakeRequest::initOptionsFromConfig();

    //Init request parameters
    _opt.type = TwitchXX::StreamType::Value::NONE;
    _opt.gameIds.emplace_back(OVERWATCH_ID);
    _opt.gameIds.emplace_back(HEARTHSTONE_ID);
}

TEST_F(StreamMetadataTest, getTop10)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getStreamsMetadata(10);
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
                auto result = TwitchXX::getStreamsMetadata(10);
                auto cursor = std::get<1>(result);
                result = TwitchXX::getStreamsMetadata(10, nullptr, cursor.c_str());
                auto streams = std::get<0>(result);
                EXPECT_EQ(streams.size(),10);
            });
}


TEST_F(StreamMetadataTest, getByGameId)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;

                auto result = TwitchXX::getStreamsMetadata(_opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_EQ(streams.size(),_opt.first);
                std::for_each(streams.begin(), streams.end(),[] (const auto& stream)
                {
                    EXPECT_TRUE(stream.GameId.Get() == OVERWATCH_ID
                                || stream.GameId.Get() == HEARTHSTONE_ID
                                || stream.GameId.Get().size() == 0);
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, getByCommunityId)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;
                _opt.type = ::TwitchXX::StreamType::Value::ALL;
                _opt.communitIds.emplace_back("2caef3bd-b3db-4eed-a748-f3ee124b33aa");

                auto result = TwitchXX::getStreamsMetadata(_opt);
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

                auto result = TwitchXX::getStreamsMetadata(_opt);
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

                auto result = TwitchXX::getStreamsMetadata(_opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(streams.size(),0);
                EXPECT_LE(streams.size(),_opt.first);
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, getByUserId)
{
    //TODO: Find any user id
    EXPECT_NO_THROW(
            {
                _opt.first = 20;
                _opt.type = ::TwitchXX::StreamType::Value::ALL;
                _opt.userIds.emplace_back("burannah");

                auto result = TwitchXX::getStreamsMetadata(_opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GE(streams.size(),0);
                EXPECT_LE(streams.size(),_opt.first);
                std::for_each(streams.begin(), streams.end(),[&] (const auto& stream)
                {
                    EXPECT_EQ( stream.UserId.Get(),_opt.userIds[0]);
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, getByUserLogin)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;
                _opt.type = ::TwitchXX::StreamType::Value::ALL;
                _opt.userLogin.emplace_back("burannah");

                auto result = TwitchXX::getStreamsMetadata(_opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GE(streams.size(),0);
                EXPECT_LE(streams.size(),_opt.first);
                std::for_each(streams.begin(), streams.end(),[&] (const auto& stream)
                {
                    EXPECT_EQ( stream.UserId.Get(),_opt.userIds[0]);
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamMetadataTest, limits)
{
    EXPECT_NO_THROW(
            {
                _opt.first = 20;

                TwitchXX::StreamMetadata::RateLimits limits;

                auto result = TwitchXX::getStreamsMetadata(_opt, &limits);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(limits.Limit, limits.Remaining);
                EXPECT_GT(limits.Limit, 0);
                EXPECT_GT(limits.Remaining, 0);
            });
}
