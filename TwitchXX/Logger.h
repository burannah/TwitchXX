//
// Created by buran on 02/04/18.
//

#ifndef TWITCHXX_LOGGER_H
#define TWITCHXX_LOGGER_H

#include <chrono>
#include <string>
#include <memory>

namespace TwitchXX
{
    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    /// Logger interface for TwitchXX libary users to implement.
    /// Derive your logging class from this and use Log::AddLogger to add it.
    /// Logger::Msg will be invoked in multiple threads.
    class Logger
    {
    public:
        /// This method will be invoked by the Log dispatcher of TwitchXX library upon a log event
        virtual void Msg(LogLevel level,
                         std::chrono::system_clock::time_point tm,
                         const std::string& msg) = 0;
    };

    /// Add logger object to Log dispatcher of TwitchXX library
    void AddLogger(std::weak_ptr<Logger> logger);

}


#endif //TWITCHXX_LOGGER_H
