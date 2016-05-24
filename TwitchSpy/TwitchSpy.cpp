// TwitchSpy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <TwitchXX.h>


int main()
{
	TwitchXX::Api api(L"8a1txctbv1nykj76c98vn7t4d66pmhe");

	//auto games = api.TopGames();
	//auto stream = api.GetStream(L"starladder1");
	auto streams = api.TopStreams(100);
	getch();
    return 0;
}

