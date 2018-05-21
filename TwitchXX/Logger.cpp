//
// Created by buran on 02/04/18.
//

#include <Logger.h>
#include <Log.h>

/// Add logger object to Log dispatcher of TwitchXX library
void TwitchXX::AddLogger(std::weak_ptr<TwitchXX::Logger> logger)
{
    Log::AddLogger(logger);
}
