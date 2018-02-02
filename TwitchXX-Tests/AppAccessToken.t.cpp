//
// Created by buran on 01/02/18.
//

#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <Auth/AppAccessToken.h>
#include <Utility.h>

class AppAccessTokenTest : public ::testing::Test
{
    void SetUp() override;
};

void AppAccessTokenTest::SetUp()
{
    Test::SetUp();

    //Init default parameters
    TwitchXX::MakeRequest::initOptionsFromConfig();
}


TEST_F(AppAccessTokenTest, Authorize)
{
    EXPECT_NO_THROW({
                        TwitchXX::AppAccessToken token;
                        EXPECT_TRUE(token.isValid());
                        EXPECT_GT(token.validTill(), std::chrono::system_clock::now());
                    });
}
