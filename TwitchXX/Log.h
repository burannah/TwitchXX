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
    /// Logger class. Singleton
    class Log
    {
        static Log log;

        std::vector<std::weak_ptr<Logger>> _loggers;

        static void Message(LogLevel level, const std::string& msg);
    public:
        static void AddLogger(std::weak_ptr<Logger> logger);    ///< Add new logger
        static void Debug(const std::string & msg);             ///< Log Debug message
        static void Info(const std::string & msg);              ///< Log Info
        static void Warn(const std::string & msg);              ///< Log Warning
        static void Error(const std::string & msg);             ///< Log Error
    };
}

#endif //TWITCHXX_LOGGER1_H
