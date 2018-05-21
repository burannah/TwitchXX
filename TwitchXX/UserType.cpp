//
// Created by buran on 05/03/18.
//

#include <UserType.h>
#include <TwitchException.h>

std::string TwitchXX::UserType::toString(TwitchXX::UserType::Value v)
{
    switch(v)
    {
        case Value::ADMIN : return "admin";
        case Value::STAFF : return "staff";
        case Value::GLOBAL_MOD : return "global_mod";
        case Value::NONE : return "";
        default:
            throw TwitchXX::TwitchException("Unsupported user type");
    }
}

TwitchXX::UserType::Value TwitchXX::UserType::fromString(const std::string &s)
{
    if(s == "") return Value::NONE;
    if(s == "global_mod") return Value::GLOBAL_MOD;
    if(s == "admin") return Value::ADMIN;
    if(s == "staff") return Value::STAFF;

    throw TwitchXX::TwitchException("Unsupported user type");
}

TwitchXX::UserType::Value TwitchXX::UserType::fromInt(int i)
{
    if(i < 0 || i > static_cast<int>(Value::GLOBAL_MOD) )
    {
        throw TwitchXX::TwitchException("Unsupported user type");
    }
    return static_cast<Value>(i);
}
