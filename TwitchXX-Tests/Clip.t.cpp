//
// Created by buran on 18/01/18.
//

#include <Clip.h>
#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <TwitchException.h>
#include <Utility.h>
#include <TestConstants.h>
#include <Api.h>


class ClipTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api;
};

TEST_F(ClipTest, GetClip)
{
    auto handle = TwitchXX::Clip::CreateAndGetHandle(_api, phoenix_id);

    EXPECT_GT(handle.Id.size(),0);
    EXPECT_GT(handle.EditUrl.size(),0);
    EXPECT_GT(handle.Limit,0);
    EXPECT_GT(handle.Remaining,0);
}

TEST_F(ClipTest, GetClip_Offline)
{
    EXPECT_THROW(TwitchXX::Clip::CreateAndGetHandle(_api, buran_id), TwitchXX::TwitchException);

}


TEST_F(ClipTest, Constructor)
{
    //Reuqest this clip: https://clips.twitch.tv/ThankfulMotionlessStinkbugCurseLit
    TwitchXX::Clip clip(_api, "ThankfulMotionlessStinkbugCurseLit");

    EXPECT_EQ(clip.Id, "ThankfulMotionlessStinkbugCurseLit");
    EXPECT_EQ(clip.Url, "https://clips.twitch.tv/ThankfulMotionlessStinkbugCurseLit");
    EXPECT_EQ(clip.EmbedUrl, "https://clips.twitch.tv/embed?clip=ThankfulMotionlessStinkbugCurseLit");
    EXPECT_EQ(clip.BroadcasterId, 28633177);
    EXPECT_EQ(clip.CreatorId, 181208335);
    EXPECT_EQ(clip.VideoId, 217784598);
    EXPECT_EQ(clip.GameId, 29595);
    EXPECT_EQ(clip.Language, "en");
    EXPECT_EQ(clip.Title, "айсайсайсайсайсайсайсайсайсайсайсайсайсайсайсайсайсайс");
    EXPECT_GE(clip.ViewCount, 216);
    EXPECT_EQ(clip.Created, TwitchXX::DateFromString("2018-01-12T12:46:09Z"));
    EXPECT_EQ(clip.Thumb, "https://clips-media-assets.twitch.tv/175389984-preview-480x272.jpg");
}
