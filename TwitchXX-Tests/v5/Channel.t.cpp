//
// Created by buran on 11/07/18.
//

#include <gtest/gtest.h>
#include <Api.h>
#include <TestUtils.h>
#include <v5/Channel.h>
#include <TestConstants.h>
#include <string>

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

TEST_F(ChannelTest, updateStatus)
{
    auto channel = TwitchXX::v5::updateChannelStatus(_api, std::to_string(buran_id), "Test status 1");

    EXPECT_EQ(channel.Status, "Test status 1");

    channel = TwitchXX::v5::updateChannelStatus(_api, std::to_string(buran_id), "");

    EXPECT_TRUE(channel.Status.empty());
}


TEST_F(ChannelTest, getEditors)
{
    auto editors = TwitchXX::v5::getChannelEditors(_api, std::to_string(buran_id));

    EXPECT_TRUE(editors.empty());
}

TEST_F(ChannelTest, getFollowers)
{
    
}
