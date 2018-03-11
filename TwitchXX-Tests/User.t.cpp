//
// Created by buran on 11/03/18.
//

#include <gtest/gtest.h>
#include <MakeRequest.h>
#include <User.h>


class UserTest : public ::testing::Test
{
protected:
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
                auto burannah = TwitchXX::getUser("", "burannah");
                EXPECT_EQ(burannah.Id, "51977856");
            });
}


TEST_F(UserTest, getOneById)
{
    EXPECT_NO_THROW(
            {
                auto burannah = TwitchXX::getUser("51977856");
                EXPECT_EQ(burannah.Login, "burannah");
            });

}


TEST_F(UserTest, getMany)
{
    EXPECT_NO_THROW(
            {
                auto result = TwitchXX::getUsers({},{"burannah", "alkali"});

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
