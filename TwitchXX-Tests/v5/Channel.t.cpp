//
// Created by buran on 11/07/18.
//

#include <gtest/gtest.h>
#include <v5/Channel.h>
#include <TestUtils.h>
#include <TestConstants.h>

class ChannelTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api {TestUtils::initOptionsFromConfigV5()};
};


TEST_F(ChannelTest, getSelf)
{
    auto channel = TwitchXX::v5::getSelfChannel(_api);

    EXPECT_EQ(channel.Name, "burannah");
}

TEST_F(ChannelTest, getChannelById)
{
    auto channel = TwitchXX::v5::getChannel(_api, std::to_string(phoenix_id));

    EXPECT_EQ(channel.Name, "waveafterwave2ndlife");
}