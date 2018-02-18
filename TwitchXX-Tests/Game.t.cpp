//
// Created by buran on 29/01/18.
//

#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <Game.h>
#include <TwitchException.h>

const std::string DOTA2_ID = "29595";
const std::string PUBG_ID = "493057";

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
    TwitchXX::Game pubg("493057");

    EXPECT_EQ("493057", pubg.Id.Get());
    EXPECT_EQ("PLAYERUNKNOWN'S BATTLEGROUNDS", pubg.Name.Get());
    EXPECT_EQ("https://static-cdn.jtvnw.net/ttv-boxart/PLAYERUNKNOWN%27S%20BATTLEGROUNDS-{width}x{height}.jpg",
              pubg.BoxArt.Get());
}

TEST_F(GameTest, Constructor2)
{
    TwitchXX::Game dota("", "Dota 2");

    EXPECT_TRUE(dota.Id.Get().size());
    EXPECT_EQ(dota.Name.Get(), "Dota 2");
}


TEST_F(GameTest, Constructor3)
{
    EXPECT_THROW(TwitchXX::Game("",""), TwitchXX::TwitchException);
}

TEST_F(GameTest, MassRequest)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getGames({DOTA2_ID, PUBG_ID});
                EXPECT_EQ(result.size(),2);
                for(const auto& game : result)
                {
                    EXPECT_EQ(game.Name.Get(), game.Id.Get() == DOTA2_ID ? "Dota 2" : "PLAYERUNKNOWN'S BATTLEGROUNDS");
                }
            }
    );
}
