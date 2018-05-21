//
// Created by buran on 03/03/18.
//

#include <TwitchException.h>
#include <Stream.h>
#include <StreamType.h>
namespace TwitchXX
{
    std::string StreamType::toString(StreamType::Value v)
    {
        switch (v)
        {
            case Value::ALL: return "all";
            case Value::LIVE: return "live";
            case Value::VODCAST: return "vodcast";
            case Value::RERUN: return "rerun";
            default:
                std::string msg = "Unsupported stream type! [" +
                                  std::to_string(static_cast<int>(v)) + "]";
                throw TwitchXX::TwitchException(msg.c_str());
        }
    }

    StreamType::Value StreamType::fromString(const std::string& s)
    {
        if(s == "all") return Value::ALL;
        if(s == "live") return Value::LIVE;
        if(s == "vodcast") return Value::VODCAST;
        if(s == "rerun") return Value::RERUN;

        std::string msg = "Unsupported stream type! [" + s + "]";
        throw TwitchXX::TwitchException(msg.c_str());
    }

    StreamType::Value StreamType::fromInt(int i)
    {
        switch (i)
        {
            case 0: return Value::ALL;
            case 1: return Value::LIVE;
            case 2: return Value::VODCAST;
            case 3: return Value::RERUN;
            default:
                std::string msg = "Unsupported stream type! [" + std::to_string(i) + "]";
                throw TwitchXX::TwitchException(msg.c_str());
        }
    }
}
