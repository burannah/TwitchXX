//
// Created by buran on 05/03/18.
//

#include "BroadcasterType.h"
#include "TwitchException.h"

std::string TwitchXX::BroadcasterType::toString(TwitchXX::BroadcasterType::Value v)
{
    switch(v)
    {
        case Value::NONE: return "";
        case Value::AFFILIATE: return "affiliate";
        case Value::PARTNER: return "partner";
        default:
            throw TwitchXX::TwitchException("Unsupported broadcaster type");
    }
}

TwitchXX::BroadcasterType::Value TwitchXX::BroadcasterType::fromString(const std::string &s)
{
    if(s == "") return Value::NONE;
    if(s == "affiliate") return Value::AFFILIATE;
    if(s == "partner") return Value::PARTNER;

    throw TwitchXX::TwitchException("Unsupported broadcaster type");
}

TwitchXX::BroadcasterType::Value TwitchXX::BroadcasterType::fromInt(int i)
{
    if(i < 0 || i > static_cast<int>(Value::AFFILIATE))
        throw TwitchXX::TwitchException("Unsupported broadcaster type");
    return static_cast<Value>(i);
}


