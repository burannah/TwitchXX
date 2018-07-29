//
// Created by buran on 11/07/18.
//

#include <gtest/gtest.h>
#include <Api.h>
#include <TestUtils.h>
#include <v5/Channel.h>
#include <TestConstants.h>
#include <string>
#include <v5/Subscription.h>
#include <TwitchException.h>

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

TEST_F(ChannelTest, getTeams)
{
    auto teams = TwitchXX::v5::getChannelTeams(_api, std::to_string(welovegames_id));

    EXPECT_EQ(teams.size(), 2);
    EXPECT_EQ(teams[0].Name, "pubgpartners");
    EXPECT_EQ(teams[1].Name, "zekeonia");
}

TEST_F(ChannelTest, getSubscribers)
{
    try
    {
        auto subs = TwitchXX::v5::getChannelSubscribers(_api, std::to_string(buran_id));
    }
    catch(const TwitchXX::TwitchException& e)
    {
        EXPECT_EQ(e.code(), 400);
        EXPECT_EQ(e.what(), std::string("Bad Request: burannah does not have a subscription program. Status code: 400"));
    }
}

TEST_F(ChannelTest, checkUserSubscribed)
{
    auto sub = TwitchXX::v5::checkChannelSubscriptionByUser(_api, std::to_string(welovegames_id), std::to_string(buran_id));

    EXPECT_TRUE(sub.Id.empty());
}
