// TwitchXX-Tests.cpp : Defines the entry point for the console application.
//

#include <gtest/gtest.h>
#include <Log.h>
#include <TestLogger.h>


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    auto logger = std::make_shared<TestLogger>();
    TwitchXX::Log::AddLogger(logger);

    return RUN_ALL_TESTS();
}

