#pragma once

#include <gtest/gtest.h>
#include <memory>
#include <TwitchXX.h>


class TwitchXXTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		_api = std::make_unique<TwitchXX::Api>(std::weak_ptr<TwitchXX::Logger>());
	}

	std::unique_ptr<TwitchXX::Api> _api;
};

