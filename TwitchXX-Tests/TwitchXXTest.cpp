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
		if (result.Offline)
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
		EXPECT_EQ(stream.Game.Get(), L"Dota 2");
	}
}

TEST_F(TwitchXXTest,FeaturedStreams)
{
	TwitchXX::TwitchFeaturedStreamsContainer result;
	ASSERT_NO_THROW(
	{
		result = _api->GetFeaturedStreams();
	});
	EXPECT_GT(result.size(), unsigned{ 0 }); //Expecting some featured streams
	EXPECT_NE(result.begin()->Title.Get(), L""); //Expecting some title;
}

TEST_F(TwitchXXTest,GetSummary)
{
	std::tuple<size_t, size_t> result;
	EXPECT_NO_THROW(
	{
		result = _api->GetSummary();
	});

	//Someone is out there... watching
	EXPECT_GT(std::get<0>(result), unsigned{ 1 }); //viewers
	EXPECT_GT(std::get<1>(result), unsigned{ 1 }); //channels

	EXPECT_NO_THROW(
	{
		result = _api->GetSummary(L"Dota 2");
	});

	//Long live Dota!
	EXPECT_GT(std::get<0>(result), unsigned{ 1 });
	EXPECT_GT(std::get<1>(result), unsigned{ 1 });
}

TEST_F(TwitchXXTest,GetFollowedStreams)
{
	EXPECT_NO_THROW(
	{
		auto result = _api->FollowedStreams();
	});
}

TEST_F(TwitchXXTest,GetChannel)
{
	EXPECT_NO_THROW(
	{
		auto result = _api->GetChannel(L"starladder1");
	});
}

TEST_F(TwitchXXTest,GetIngests)
{
	TwitchXX::TwitchIngestsContainer result;

	EXPECT_NO_THROW(
	{
		result = _api->GetIngetst();
	});

	EXPECT_GT(result.size(), 0U);
}

