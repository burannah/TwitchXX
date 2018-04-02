//
// Created by buran on 02/04/18.
//

#include <Log.h>
#include <Logger.h>
#include <memory>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <iterator>

namespace TwitchXX
{
    Log Log::log;

    void Log::AddLogger(std::weak_ptr<TwitchXX::Logger> logger)
    {
        log._loggers.push_back(logger);
    }

    void Log::Debug(const std::string &msg)
    {
        if(log._level > LogLevel::DEBUG) return;
        Message(LogLevel::DEBUG, msg);
    }

    void Log::Info(const std::string &msg)
    {
        if(log._level > LogLevel::INFO) return;
        Message(LogLevel::INFO, msg);
    }

    void Log::Warn(const std::string &msg)
    {
        if(log._level > LogLevel::WARN) return;
        Message(LogLevel::WARN, msg);
    }

    void Log::Error(const std::string &msg)
    {
        if(log._level > LogLevel::ERROR) return;
        Message(LogLevel::WARN, msg);
    }

    void Log::Message(LogLevel level, const std::string &msg)
    {
        auto tp = std::chrono::system_clock::now();
        std::for_each(std::begin(log._loggers), std::end(log._loggers),
                      [&](std::weak_ptr<Logger> logger)
                        {
                            auto sp = logger.lock();
                            if(sp)
                            {
                                sp->Msg(level, tp, msg);
                            }
                        }
        );

    }
}

