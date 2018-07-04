//
// Created by buran on 04/07/18.
//

#include <gtest/gtest.h>
#include <Api.h>
#include <TestUtils.h>
#include <v5/Action.h>
#include <TestConstants.h>

class ActionTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api {TestUtils::initOptionsFromConfigV5()};
};

TEST_F(ActionTest, getPhoenix)
{
    auto cheermotes = TwitchXX::v5::getBits(_api, std::to_string(phoenix_id));

    EXPECT_EQ(cheermotes.size(), 0);
}

TEST_F(ActionTest, getAll)
{
    auto cheermotes = TwitchXX::v5::getBits(_api);

    EXPECT_EQ(cheermotes.size(), 0);
}
