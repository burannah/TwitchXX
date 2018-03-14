//
// Created by buran on 14/03/18.
//

#include <VideoType.h>
#include <map>
#include <TwitchException.h>

std::string TwitchXX::VideoType::toString(TwitchXX::VideoType::Value v)
{
    const static std::map<Value, std::string> strs {{Value::ALL, "all"},
                                                    {Value::UPLOAD, "upload"},
                                                    {Value::ARCHIVE, "archive"},
                                                    {Value::HIGHLIGHT, "highlight"}};

    try
    {
        return strs.at(v);
    }
    catch(const std::out_of_range& e)
    {
        throw TwitchException("Unsupported video type value");
    }
}

TwitchXX::VideoType::Value TwitchXX::VideoType::fromString(const std::string &s)
{
    const static std::map<std::string, Value> strs {{"all", Value::ALL},
                                                    {"upload", Value::UPLOAD},
                                                    {"archive", Value::ARCHIVE},
                                                    {"highlight", Value::HIGHLIGHT}};

    try
    {
        return strs.at(s);
    }
    catch(const std::out_of_range& e)
    {
        throw TwitchException("Unable to parse video type value from string");
    }
}

TwitchXX::VideoType::Value TwitchXX::VideoType::fromInt(int i)
{
    if(static_cast<int>(Value::ALL) > i || static_cast<int>(Value::HIGHLIGHT) < i)
    {
        throw TwitchException("Value out of range of video type");
    }

    return static_cast<Value>(i);
}
