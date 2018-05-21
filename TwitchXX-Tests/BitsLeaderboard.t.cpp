//
// Created by buran on 19/05/18.
//

#include <gtest/gtest.h>
#include <Api.h>
#include <BitsLeaderboardOptions.h>
#include <BitsLeaderboardEntry.h>

class BitsLeaderboardTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api;
};


TEST_F(BitsLeaderboardTest, ge10)
{
    TwitchXX::BitsLeaderboardOptions opt;

    auto result = TwitchXX::getBitsLeaderborard(_api, opt);

    EXPECT_LE(result.size(), 10);
}
