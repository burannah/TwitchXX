//
// Created by buran on 11/03/18.
//

#include <gtest/gtest.h>
#include <User.h>
#include <Api.h>


class UserTest : public ::testing::Test
{
protected:
    TwitchXX::Api _api;

    void SetUp() override;
};

void UserTest::SetUp()
{
    Test::SetUp();

    //Init default parameters
    TwitchXX::MakeRequest::initOptionsFromConfig();
}


TEST_F(UserTest, getOneByName)
{
    EXPECT_NO_THROW(
            {
                auto burannah = TwitchXX::getUser(_api, "", "burannah");
                EXPECT_EQ(burannah.Id, "51977856");
            });
}


TEST_F(UserTest, getOneById)
{
    EXPECT_NO_THROW(
            {
                auto burannah = TwitchXX::getUser(_api, "51977856", std::__cxx11::string());
                EXPECT_EQ(burannah.Login, "burannah");
            });

}


TEST_F(UserTest, getMany)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getUsers(_api, {}, {"burannah", "alkali"});

                auto findByLogin = [](const auto& login)
                {
                    return [&](const auto& val)
                    {
                        return val.Login == login;
                    };
                };
                EXPECT_EQ(result.size(),2);
                EXPECT_NE(std::find_if(result.begin(),result.end(),findByLogin("burannah")),result.end());
                EXPECT_NE(std::find_if(result.begin(),result.end(),findByLogin("alkali")),result.end());
            });
}

TEST_F(UserTest, updateDescription)
{
    const std::string desc = "Super puper test";
    auto burannah = TwitchXX::getUser(_api, "", "burannah");
    auto burannah2 = TwitchXX::updateUserDescription(_api, desc);
    EXPECT_NE(burannah.Description, burannah2.Description);
    EXPECT_EQ(burannah2.Description, desc);
    burannah2 = TwitchXX::updateUserDescription(_api, burannah.Description);
    EXPECT_EQ(burannah.Description, burannah2.Description);
    EXPECT_NE(burannah2.Description, desc);
}
