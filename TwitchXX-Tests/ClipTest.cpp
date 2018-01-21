//
// Created by buran on 18/01/18.
//

#include <Clip.h>
#include <gtest/gtest.h>
#include <MakeRequest.h>


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
    //TODO: Fix with proper broadcaster_id
    TwitchXX::MakeRequest::initOptionsFromConfig();
    auto handle = TwitchXX::Clip::CreateAndGetHandle("starladder1");

    EXPECT_GT(handle.Id.size(),0);
    EXPECT_GT(handle.EditUrl.size(),0);
    EXPECT_GT(handle.Limit,0);
    EXPECT_GT(handle.Remaining,0);
}

TEST(ClipTest, Constructor)
{
    //Reuqest this clip: https://clips.twitch.tv/ThankfulMotionlessStinkbugCurseLit
    TwitchXX::Clip clip("ThankfulMotionlessStinkbugCurseLit");

    //TODO: Check clip values;

}
