//
// Created by buran on 29/01/18.
//

#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <Game.h>
#include <TwitchException.h>
#include <TestConstants.h>


class GameTest : public ::testing::Test
{
    void SetUp() override;
};

void GameTest::SetUp()
{
    Test::SetUp();

    //Init default parameters
    TwitchXX::MakeRequest::initOptionsFromConfig();
}


TEST_F(GameTest, Constructor1)
{
    TwitchXX::Game pubg(493057);

    EXPECT_EQ(493057, pubg.Id);
    EXPECT_EQ("PLAYERUNKNOWN'S BATTLEGROUNDS", pubg.Name);
    EXPECT_EQ("https://static-cdn.jtvnw.net/ttv-boxart/PLAYERUNKNOWN%27S%20BATTLEGROUNDS-{width}x{height}.jpg",
              pubg.BoxArt);
}

TEST_F(GameTest, Constructor2)
{
    TwitchXX::Game dota(0 , "Dota 2");

    EXPECT_TRUE(dota.Id);
    EXPECT_EQ(dota.Name, "Dota 2");
}


TEST_F(GameTest, Constructor3)
{
    EXPECT_THROW(TwitchXX::Game(0 ,""), TwitchXX::TwitchException);
}

TEST_F(GameTest, MassRequest)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getGames({DOTA2_ID, PUBG_ID});
                EXPECT_EQ(result.size(),2);
                for(const auto& game : result)
                {
                    EXPECT_EQ(game.Name, game.Id == DOTA2_ID ? "Dota 2" : "PLAYERUNKNOWN'S BATTLEGROUNDS");
                }
            }
    );
}

TEST_F(GameTest, getTopGames_first20)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getTopGames(20);

                EXPECT_EQ(std::get<0>(result).size(),20);
                EXPECT_GT(std::get<1>(result).size(),5);
            }
    );
}


TEST_F(GameTest, getTopGames_exception_to_many)
{
    EXPECT_THROW({
                     TwitchXX::getTopGames(101);
                 },
                 TwitchXX::TwitchException);
}


TEST_F(GameTest, getTopGames_cursors)
{
    EXPECT_NO_THROW({
        auto result = TwitchXX::getTopGames(10);
        auto game = std::get<0>(result)[4];
        auto cursor = std::get<1>(result);

        auto result2 = TwitchXX::getTopGames(10,cursor.c_str());
        auto cursor2 = std::get<1>(result2);
        auto game2 = std::get<0>(TwitchXX::getTopGames(15, nullptr, cursor2.c_str()))[0];
        /* TODO: topic created
        EXPECT_EQ(game.Name.Get(), game2.Name.Get());*/
                    });
}
