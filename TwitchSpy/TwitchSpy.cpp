// TwitchSpy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <TwitchXX.h>


int main()
{
	TwitchXX::Api api;

	auto games = api.Games();
    return 0;
}

