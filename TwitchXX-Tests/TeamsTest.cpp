#include "TeamsTest.h"


TEST_F(TeamsTest, GetTeams)
{
	TwitchXX::TwitchTeamsContainer result;
	ASSERT_NO_THROW(
	{
		result = _api->GetTeams();
	});

	EXPECT_GT(result.size(), 1U);
}

TEST_F(TeamsTest, GetTeam)
{
	TwitchXX::TwitchTeam result;
	ASSERT_NO_THROW(
	{
		result = _api->GetTeam(U("testteam"));
	});
}