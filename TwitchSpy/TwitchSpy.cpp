// TwitchSpy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <TwitchXX.h>


int main()
{
	TwitchXX::Api api(L"8a1txctbv1nykj76c98vn7t4d66pmhe");

	auto games = api.TopGames(100);
	auto stream = api.GetStream(L"cheatbanned");
	TwitchXX::options opt { {L"stream_type", L"playlist"}};
	auto streams = api.TopStreams(100, opt);
	auto featured = api.GetFeaturedStreams();
	auto summary_all = api.GetSummary();
	auto summary_dota = api.GetSummary(L"Dota 2");
	getch();
    return 0;
}

