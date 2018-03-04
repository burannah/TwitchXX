//
// Created by buran on 28/02/18.
//

#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <Stream.h>
#include <TestConstants.h>

class StreamTest : public ::testing::Test
{
    void SetUp() override;
};

void StreamTest::SetUp()
{
    Test::SetUp();

    //Init default parameters
    TwitchXX::MakeRequest::initOptionsFromConfig();
}

TEST_F(StreamTest, getTop10)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getStreams(10);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_EQ(streams.size(),10);
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamTest, getNex10)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getStreams(10);
                auto cursor = std::get<1>(result);
                result = TwitchXX::getStreams(10, cursor.c_str());
                auto streams = std::get<0>(result);
                EXPECT_EQ(streams.size(),10);
            });
}


TEST_F(StreamTest, getByGameId)
{
    EXPECT_NO_THROW(
            {
                TwitchXX::StreamsOptions opt;
                opt.first = 20;
                opt.type = ::TwitchXX::StreamType::Value::ALL;
                opt.gameIds.push_back(DOTA2_ID);

                auto result = TwitchXX::getStreams(opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_EQ(streams.size(),opt.first);
                std::for_each(streams.begin(), streams.end(),[] (const auto& stream)
                {
                    EXPECT_EQ(stream.GameId.Get(),DOTA2_ID);
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamTest, getByCommunityId)
{
    EXPECT_NO_THROW(
            {
                TwitchXX::StreamsOptions opt;
                opt.first = 20;
                opt.type = ::TwitchXX::StreamType::Value::ALL;
                opt.communitIds.emplace_back("848d95be-90b3-44a5-b143-6e373754c382");

                auto result = TwitchXX::getStreams(opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(streams.size(),0);
                EXPECT_LE(streams.size(),opt.first);
                std::for_each(streams.begin(), streams.end(),[] (const auto& stream)
                {
                    const auto& cmmtys = stream.CommunityIds.Get();
                    auto it = std::find(cmmtys.begin(), cmmtys.end(),
                                        "848d95be-90b3-44a5-b143-6e373754c382");
                    EXPECT_TRUE( it != cmmtys.end());
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamTest, getByLang)
{
    EXPECT_NO_THROW(
            {
                TwitchXX::StreamsOptions opt;
                opt.first = 20;
                opt.type = ::TwitchXX::StreamType::Value::ALL;
                opt.langs.emplace_back("ru");

                auto result = TwitchXX::getStreams(opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(streams.size(),0);
                EXPECT_LE(streams.size(),opt.first);
                std::for_each(streams.begin(), streams.end(),[] (const auto& stream)
                {
                    EXPECT_EQ( stream.Language.Get(),"ru");
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamTest, getByType)
{
    EXPECT_NO_THROW(
            {
                TwitchXX::StreamsOptions opt;
                opt.first = 20;
                opt.type = ::TwitchXX::StreamType::Value::LIVE;

                auto result = TwitchXX::getStreams(opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GT(streams.size(),0);
                EXPECT_LE(streams.size(),opt.first);
                std::for_each(streams.begin(), streams.end(),[&] (const auto& stream)
                {
                    EXPECT_EQ( stream.Type.Get(),opt.type);
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamTest, getByUserId)
{
    //TODO: Find any user id
    EXPECT_NO_THROW(
            {
                TwitchXX::StreamsOptions opt;
                opt.first = 20;
                opt.type = ::TwitchXX::StreamType::Value::ALL;
                opt.userIds.emplace_back("burannah");

                auto result = TwitchXX::getStreams(opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GE(streams.size(),0);
                EXPECT_LE(streams.size(),opt.first);
                std::for_each(streams.begin(), streams.end(),[&] (const auto& stream)
                {
                    EXPECT_EQ( stream.UserId.Get(),opt.userIds[0]);
                });
                EXPECT_GE(cursor.size(),5);
            });
}

TEST_F(StreamTest, getByUserLogin)
{
    EXPECT_NO_THROW(
            {
                TwitchXX::StreamsOptions opt;
                opt.first = 20;
                opt.type = ::TwitchXX::StreamType::Value::ALL;
                opt.userLogin.emplace_back("burannah");

                auto result = TwitchXX::getStreams(opt);
                auto streams = std::get<0>(result);
                auto cursor = std::get<1>(result);
                EXPECT_GE(streams.size(),0);
                EXPECT_LE(streams.size(),opt.first);
                std::for_each(streams.begin(), streams.end(),[&] (const auto& stream)
                {
                    EXPECT_EQ( stream.UserId.Get(),opt.userIds[0]);
                });
                EXPECT_GE(cursor.size(),5);
            });
}