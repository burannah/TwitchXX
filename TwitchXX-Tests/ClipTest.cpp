//
// Created by buran on 18/01/18.
//

#include <Clip.h>
#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <TwitchException.h>
#include <Utility.h>


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


TEST_F(ClipTest, Constructor)
{
    //Reuqest this clip: https://clips.twitch.tv/ThankfulMotionlessStinkbugCurseLit
    TwitchXX::Clip clip("ThankfulMotionlessStinkbugCurseLit");

    EXPECT_EQ(clip.Id.Get(), "ThankfulMotionlessStinkbugCurseLit");
    EXPECT_EQ(clip.Url.Get(), "https://clips.twitch.tv/ThankfulMotionlessStinkbugCurseLit");
    EXPECT_EQ(clip.EmbedUrl.Get(), "https://clips.twitch.tv/embed?clip=ThankfulMotionlessStinkbugCurseLit");
    EXPECT_EQ(clip.BroadcasterId.Get(), "28633177");
    EXPECT_EQ(clip.CreatorId.Get(), "181208335");
    EXPECT_EQ(clip.VideoId.Get(), "217784598");
    EXPECT_EQ(clip.GameId.Get(), "29595");
    EXPECT_EQ(clip.Language.Get(), "en");
    EXPECT_EQ(clip.Title.Get(), "айсайсайсайсайсайсайсайсайсайсайсайсайсайсайсайсайсайс");
    EXPECT_GE(clip.ViewCount.Get(), 216);
    EXPECT_EQ(clip.Created.Get(), TwitchXX::DateFromString("2018-01-12T12:46:09Z"));
    EXPECT_EQ(clip.Thumb.Get(), "https://clips-media-assets.twitch.tv/175389984-preview-480x272.jpg");
}
