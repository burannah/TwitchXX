//
// Created by buran on 18/01/18.
//

#include <Clip.h>
#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <TwitchException.h>


class ClipTest : public ::testing::Test
{
    virtual void SetUp();
};

void ClipTest::SetUp()
{
    //Init default parameters
    TwitchXX::MakeRequest::initOptionsFromConfig();
}

TEST_F(ClipTest, GetClip)
{
    //TODO: Fix with get any live channel first
    TwitchXX::MakeRequest::initOptionsFromConfig();
    auto handle = TwitchXX::Clip::CreateAndGetHandle("44322889");

    EXPECT_GT(handle.Id.size(),0);
    EXPECT_GT(handle.EditUrl.size(),0);
    EXPECT_GT(handle.Limit,0);
    EXPECT_GT(handle.Remaining,0);
}

TEST_F(ClipTest, GetClip_Offline)
{
    //TODO: Fix with always offline channel id
    TwitchXX::MakeRequest::initOptionsFromConfig();
    EXPECT_THROW(TwitchXX::Clip::CreateAndGetHandle("44322889"), TwitchXX::TwitchException);

}


TEST(ClipTest, Constructor)
{
    //Reuqest this clip: https://clips.twitch.tv/ThankfulMotionlessStinkbugCurseLit
    TwitchXX::Clip clip("ThankfulMotionlessStinkbugCurseLit");

    //TODO: Check clip values;

}
