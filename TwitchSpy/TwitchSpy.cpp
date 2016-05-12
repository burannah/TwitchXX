// TwitchSpy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <TwitchXX.h>


int main()
{
	TwitchXX::Api api;

	auto games = api.TopGames();
	getch();
    return 0;
}

