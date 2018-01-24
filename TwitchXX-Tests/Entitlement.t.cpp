//
// Created by buran on 24/01/18.
//

#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <Entitlement.h>
#include <Utility.h>
#include <memory>

class EntitlementTest : public ::testing::Test
{
    void SetUp() override;
};

void EntitlementTest::SetUp()
{
    Test::SetUp();

    //Init default parameters
    TwitchXX::MakeRequest::initOptionsFromConfig();
}

TEST_F(EntitlementTest, Constructor)
{
    std::unique_ptr<TwitchXX::Entitlement> entitlement;
    std::string id = "something_for_testing" + TwitchXX::DateToString(std::chrono::system_clock::now());
    EXPECT_NO_THROW(entitlement = std::make_unique<TwitchXX::Entitlement>(id));

    EXPECT_GE(entitlement->Url.Get().length(),15);
}
