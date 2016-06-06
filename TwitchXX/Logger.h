#pragma once

#include <string>
#include <list>
#include <memory>
#include <algorithm>

namespace TwitchXX
{
	class MongoLogger;

	class Logger
	{
	public:
		Logger() {} ;

		virtual ~Logger()
		{
		}

		enum class LogLevel
		{
			Message,
			Warning,
			Error,
			Debug
		};
		virtual void Log(std::wstring msg, LogLevel level = LogLevel::Message) const
		{
			//This log doesnt do any actual logging
			std::for_each(_subscribers.begin(), _subscribers.end(), [&](const auto& log) {log->Log(msg, level); });
		}
		virtual void Subscribe(std::shared_ptr<Logger> log)
		{
			_subscribers.push_back(log);
		};

	private:
		std::list<std::shared_ptr<Logger>> _subscribers;
	};
}
