//
// Created by buran on 12/05/18.
//

#include <TestLogger.h>

#include <sstream>
#include <iostream>

void TestLogger::Msg(TwitchXX::LogLevel level, std::chrono::system_clock::time_point tm, const std::string &msg)
{
    std::lock_guard<std::mutex> lock(_lock);
    std::stringstream ss;

    std::time_t ttp = std::chrono::system_clock::to_time_t(tm);
    std::string time(std::ctime(&ttp));

    ss << "[" << time.substr(0,time.size()-1) << "]";

    switch(level)
    {
        case TwitchXX::LogLevel::DEBUG:
            ss << "[DEBUG]:";
            break;
        case TwitchXX::LogLevel::INFO:
            ss << "[INFO]:";
            break;
        case TwitchXX::LogLevel::WARN:
            ss << "[WARN]:";
            break;
        case TwitchXX::LogLevel::ERROR:
            ss << "[ERROR]:";
        default:
            ss << "[UNKNOWN!("<< static_cast<int>(level) << ")]:";
    }

    ss << msg;

    std::cerr << ss.str() << "\n";
}
