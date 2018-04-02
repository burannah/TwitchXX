//
// Created by buran on 02/04/18.
//

#ifndef TWITCHXX_LOGGER1_H
#define TWITCHXX_LOGGER1_H

#include <memory>
#include <vector>

#include <Logger.h>

namespace TwitchXX
{
    class Log
    {
        static Log log;

        std::vector<std::weak_ptr<Logger>> _loggers;
        LogLevel                           _level;

        explicit Log(LogLevel level = LogLevel::DEBUG)
                :_level(level)
        {}

        static void Message(LogLevel level, const std::string& msg);
    public:
        static void AddLogger(std::weak_ptr<Logger> logger);
        static void Debug(const std::string & msg);
        static void Info(const std::string & msg);
        static void Warn(const std::string & msg);
        static void Error(const std::string & msg);
    };
}

#endif //TWITCHXX_LOGGER1_H
