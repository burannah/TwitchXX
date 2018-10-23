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
#include <thread>

namespace TwitchXX
{
    Log Log::log;

    void Log::AddLogger(std::weak_ptr<TwitchXX::Logger> logger)
    {
        log._loggers.push_back(logger);
    }

    void Log::Debug(const std::string &msg)
    {
        Message(LogLevel::DEBUG, msg);
    }

    void Log::Info(const std::string &msg)
    {
        Message(LogLevel::INFO, msg);
    }

    void Log::Warn(const std::string &msg)
    {
        Message(LogLevel::WARN, msg);
    }

    void Log::Error(const std::string &msg)
    {
        Message(LogLevel::ERROR, msg);
    }

    void Log::Message(LogLevel level, const std::string &msg)
    {
        auto tp = std::chrono::system_clock::now();
        std::thread log_thread([tp, level, msg](){
            for(const auto& logger: log._loggers)
            {
                auto sp = logger.lock();
                if(sp)
                {
                  sp->Msg(level, tp, msg);
                }
            }
        });
        log_thread.detach();
    }
}

