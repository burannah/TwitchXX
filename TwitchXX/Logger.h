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

    class Logger
    {
    public:
        virtual void Msg(LogLevel level,
                         std::chrono::system_clock::time_point tm,
                         const std::string& msg) = 0;
    };

    void AddLogger(std::weak_ptr<Logger> logger);

}


#endif //TWITCHXX_LOGGER_H
