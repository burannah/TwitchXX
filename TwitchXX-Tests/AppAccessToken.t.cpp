//
// Created by buran on 01/02/18.
//

#include <gtest/gtest.h>
#include <Auth/AppAccessToken.h>
#include <Utility.h>
#include "TestUtils.h"

class AppAccessTokenTest : public ::testing::Test
{
public:
    TwitchXX::options _opt = TestUtils::initOptionsFromConfig();
};


TEST_F(AppAccessTokenTest, Authorize)
{
    EXPECT_NO_THROW({
                        TwitchXX::AppAccessToken token(_opt.at("api_key"),
                                                       _opt.at("client_secret"));
                        EXPECT_TRUE(token.isValid());
                        EXPECT_GT(token.validTill(), std::chrono::system_clock::now());
                    });
}
