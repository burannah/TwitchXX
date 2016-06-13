#pragma once

#include <gtest/gtest.h>
#include <memory>
#include <TwitchXX.h>
#include <iostream>

class TwitchXXTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		_api = std::make_unique<TwitchXX::Api>();
	}

	void TearDown() override
	{
		std::wcout << "TwitchXXTest: TearDown" << "\n";
	}

	std::unique_ptr<TwitchXX::Api> _api;
};

