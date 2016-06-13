#include "TwitchXXTest.h"
#include <TwitchXX.h>
#include <TwitchStream.h>


TEST_F(TwitchXXTest, Constructor_No_Throw)
{
	EXPECT_NO_THROW({ 
		TwitchXX::Api api;
	});
}

TEST_F(TwitchXXTest,TopGames)
{
	TwitchXX::TwitchGamesVector result;
	EXPECT_NO_THROW({
		result = _api->TopGames(100);
	});

	EXPECT_EQ(result.size(), 100);
}

TEST_F(TwitchXXTest,GetStream)
{
	TwitchXX::TwitchStream result;
	EXPECT_NO_THROW(
	{
		result = _api->GetStream(L"starladder1");	
		if (result.Offline())
		{
			ASSERT_EQ(result.Name(), L"");
		}
		else
		{
			ASSERT_EQ(result.Name(), L"starladder1");
		}
	});
}

TEST_F(TwitchXXTest,TopStreams)
{
	TwitchXX::TwitchStreamsVector result;
	EXPECT_NO_THROW(
	{
		result = _api->TopStreams(100,{ { L"game", L"Dota 2" } });
	});
	EXPECT_LE(result.size(), unsigned{ 100 });
	for (auto& stream : result)
	{
		EXPECT_EQ(stream.Game(), L"Dota 2");
	}
}