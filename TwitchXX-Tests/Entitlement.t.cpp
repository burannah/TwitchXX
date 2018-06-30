//
// Created by buran on 24/01/18.
//

#include <gtest/gtest.h>
#include <Entitlement.h>
#include <Utility.h>
#include <memory>
#include <Api.h>
#include "TestUtils.h"

class EntitlementTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api{TestUtils::initOptionsFromConfig()};
};

TEST_F(EntitlementTest, DISABLED_Constructor)
{
    std::unique_ptr<TwitchXX::Entitlement> entitlement;
    std::string id = "something_for_testing" + TwitchXX::DateToString(std::chrono::system_clock::now());
    EXPECT_NO_THROW(entitlement = std::make_unique<TwitchXX::Entitlement>(_api, id,
                                                                          TwitchXX::Entitlement::Type::bulk_drops_grant));

    EXPECT_GE(entitlement->Url.length(),15);
}
