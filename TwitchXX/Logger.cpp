//
// Created by buran on 02/04/18.
//

#include <Logger.h>
#include <Log.h>


void TwitchXX::AddLogger(std::weak_ptr<TwitchXX::Logger> logger)
{
    Log::AddLogger(logger);
}
