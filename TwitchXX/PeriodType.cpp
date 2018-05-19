//
// Created by buran on 14/03/18.
//

#include <PeriodType.h>
#include <TwitchException.h>

std::string TwitchXX::PeriodType::toString(TwitchXX::PeriodType::Value v)
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

TwitchXX::PeriodType::Value TwitchXX::PeriodType::fromString(const std::string &s)
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

TwitchXX::PeriodType::Value TwitchXX::PeriodType::fromInt(int i)
{
    if(static_cast<int>(Value::ALL) > i || static_cast<int>(Value::MONTH) < i)
    {
        throw TwitchException("Value is not within PeriodType range");
    }
    return static_cast<Value>(i);
}
