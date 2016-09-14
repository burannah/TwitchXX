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
	TwitchXX::TwitchGamesContainer result;
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
		result = _api->GetStream(U("starladder1"));
		if (result.Offline)
		{
			ASSERT_EQ(result.Name(), U(""));
		}
		else
		{
			ASSERT_EQ(result.Name(), U("starladder1"));
		}
	});
}

TEST_F(TwitchXXTest,TopStreams)
{
	TwitchXX::TwitchStreamsContainer result;
	EXPECT_NO_THROW(
	{
		result = _api->TopStreams(100,{ { U("game"), U("Dota 2") } });
	});
	EXPECT_LE(result.size(), 100U);
	for (auto& stream : result)
	{
		EXPECT_EQ(stream.Game.Get(), U("Dota 2"));
	}
}

TEST_F(TwitchXXTest,FeaturedStreams)
{
	TwitchXX::TwitchFeaturedStreamsContainer result;
	ASSERT_NO_THROW(
	{
		result = _api->GetFeaturedStreams();
	});
	EXPECT_GT(result.size(), 0u); //Expecting some featured streams
	EXPECT_NE(result.begin()->Title.Get(), U("")); //Expecting some title;
}

TEST_F(TwitchXXTest,GetSummary)
{
	std::tuple<size_t, size_t> result;
	EXPECT_NO_THROW(
	{
		result = _api->GetSummary();
	});

	//Someone is out there... watching
	EXPECT_GT(std::get<0>(result), 1U); //viewers
	EXPECT_GT(std::get<1>(result), 1U); //channels

	EXPECT_NO_THROW(
	{
		result = _api->GetSummary(U("Dota 2"));
	});

	//Long live Dota!
	EXPECT_GT(std::get<0>(result), 1U);
	EXPECT_GT(std::get<1>(result), 1U);
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
		auto result = _api->GetChannel(U("starladder1"));
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

