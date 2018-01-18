//
// Created by buran on 18/01/18.
//

#include <Clip.h>
#include <gtest/gtest.h>
#include <thread>

TEST(ClipTest, GetClip)
{
    //TODO: Fix with proper broadcaster_id
    auto handle = TwitchXX::Clip::CreateAndGetHandle(U("starladder1"));

    EXPECT_GT(handle.Id.size(),0);
    EXPECT_GT(handle.EditUrl.size(),0);
    EXPECT_GT(handle.Limit,0);
    EXPECT_GT(handle.Remaining,0);
}

TEST(ClipTest, Constructor)
{
    //Reuqest this clip: https://clips.twitch.tv/ThankfulMotionlessStinkbugCurseLit
    TwitchXX::Clip clip(U("ThankfulMotionlessStinkbugCurseLit"));

    //TODO: Check clip values;

}
