//
// Created by buran on 04/02/18.
//

#include <gtest/gtest.h>
#include <Auth/UserAccessToken.h>
#include <RequestOnce.h>
#include "TestUtils.h"

class UserAccessTokenTest : public ::testing::Test
{
public:
    void SetUp() override;
    TwitchXX::options _opt;
};

void UserAccessTokenTest::SetUp()
{
    ::testing::Test::SetUp();

    _opt = TestUtils::initOptionsFromConfig();
}


TEST_F(UserAccessTokenTest, isValid)
{
    EXPECT_NO_THROW({
        TwitchXX::UserAccessToken token{_opt.at("token")};
        EXPECT_TRUE(token.isValid());
                    });
}


TEST_F(UserAccessTokenTest, validTill)
{
    EXPECT_NO_THROW({
        TwitchXX::UserAccessToken token{_opt.at("token")};
        auto expected_till = std::chrono::system_clock::now() + std::chrono::hours(24*7) - std::chrono::seconds(1);
        auto valid_till = token.validTill();
        auto delta = std::chrono::minutes(1);

        EXPECT_LE(expected_till, token.validTill());
                    });
}


TEST_F(UserAccessTokenTest, get)
{
    EXPECT_NO_THROW({
        TwitchXX::UserAccessToken token{_opt.at("token")};
        EXPECT_EQ(token.get(TwitchXX::AuthScope::USER_EDIT), "Bearer " + _opt["token"]);
                    });
}
