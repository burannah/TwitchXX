//
// Created by buran on 14/03/18.
//

#include <VideoPeriodType.h>
#include <TwitchException.h>

std::string TwitchXX::VideoPeriodType::toString(TwitchXX::VideoPeriodType::Value v)
{
    static const std::map<Value, std::string> strs{{Value::ALL, "all"}, {Value::DAY, "day"}, {Value::WEEK, "week"}, {Value::MONTH, "month"}};
    try
    {
        return strs.at(v);
    }
    catch(const std::out_of_range& e)
    {
        throw TwitchException("Value type is not supported");
    }
}

TwitchXX::VideoPeriodType::Value TwitchXX::VideoPeriodType::fromString(const std::string &s)
{
    static const std::map<std::string,Value> strs{{"all", Value::ALL}, {"day", Value::DAY}, {"week", Value::WEEK}, {"month", Value::MONTH}};
    try
    {
        return strs.at(s);
    }
    catch(const std::out_of_range& e)
    {
        throw TwitchException("Can not convert string to period type");
    }
}

TwitchXX::VideoPeriodType::Value TwitchXX::VideoPeriodType::fromInt(int i)
{
    if(static_cast<int>(Value::ALL) > i || static_cast<int>(Value::MONTH) < i)
    {
        throw TwitchException("Value is not within VideoPeriodType range");
    }
    return static_cast<Value>(i);
}
