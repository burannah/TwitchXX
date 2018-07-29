//
// Created by buran on 7/28/18.
//

#include "Direction.h"

#include <sstream>
#include <Log.h>
#include <TwitchException.h>


namespace TwitchXX
{
    Direction::Value Direction::fromString(const std::string& s)
    {
        if(s == "asc") return Direction::Value::ASC;
    }

    std::string Direction::toString(TwitchXX::Direction::Value v)
    {
        switch (v)
        {
            case Value::ASC : return "asc";
            case Value::DESC : return "desc";
            default:
                std::stringstream ss;
                ss << "Unknown direction value " << static_cast<int>(v);
                Log::Error(ss.str());
                throw TwitchException(ss.str().c_str());
        }
    }
}