//
// Created by buran on 14/03/18.
//

#include <map>
#include <VideoSortType.h>
#include <TwitchException.h>

std::string TwitchXX::VideoSortType::toString(TwitchXX::VideoSortType::Value v)
{
    static const std::map<Value, std::string> strs {{Value::TIME, "time"},
                                                    {Value::TRENDING, "trending"},
                                                    {Value::VIEWS, "views"}};
    try
    {
        return strs.at(v);
    }
    catch(const std::out_of_range& e)
    {
        throw TwitchException("Unsupported video sort type value");
    }
}

TwitchXX::VideoSortType::Value TwitchXX::VideoSortType::fromString(const std::string &s)
{
    static const std::map<std::string, Value> strs {{"time", Value::TIME},
                                                    {"trending", Value::TRENDING},
                                                    {"views", Value::VIEWS}};
    try
    {
        return strs.at(s);
    }
    catch(const std::out_of_range& e)
    {
        throw TwitchException("Can not parse string into video sorting type");
    }
}

TwitchXX::VideoSortType::Value TwitchXX::VideoSortType::fromInt(int i)
{
    if(static_cast<int>(Value::VIEWS) < i || static_cast<int>(Value::TIME) > i)
    {
        throw TwitchException("Integer value is out of range of sorting type");
    }
    return static_cast<Value>(i);
}


