#pragma once

#include <string>
#include <list>
#include <memory>
#include <algorithm>

namespace TwitchXX
{
	///Class and interface for this library's loggers.
	/**
	* You can derive from this class, implement your own logger and add it to the api object (TwitchXX::Api::AddLogger()).
	* These loggers will be "chained" - so you can get twitch api logs in multiple plces simultaniously.
	*/
	class Logger
	{
	public:
#ifdef _WIN32
		using string_t = std::wstring;
    using stringstream_t = std::wstringstream;
#else
		using string_t = std::string;
		using stringstream_t = std::stringstream;
#endif

		///Destructor
		virtual ~Logger()
		{
		}

		///Default copy assigment
		Logger& operator=(const Logger&) = default;
		///Default move assigment
		Logger& operator=(Logger&&) = default;

		///Log level enum.
		/**
		* In future Debug messages will only be showed if library compiled with DEBUG flag (to be decided).
		*/
		enum class LogLevel
		{
			Message, ///< Message
			Warning, ///< Warning
			Error, ///< Error
			Debug ///< Debug
		};

		///Send messages to all subscribed loggers
		/**
		* Doesn't do any actual logging. Just check that all objects are alive and broadcast incoming message to them.
		*/
		virtual void Log(utility::string_t msg, LogLevel level = LogLevel::Message)
		{
			_subscribers.remove_if([](const auto& log) { return log.expired(); });
			std::for_each(_subscribers.begin(), _subscribers.end(), [&](const auto& log) {if (auto sp = log.lock()) { sp->Log(msg, level); } });
		}

		///Subscribe a logger.
		void Subscribe(std::weak_ptr<Logger> log)
		{
			_subscribers.push_back(log);
		};

	private:
		std::list<std::weak_ptr<Logger>> _subscribers;
	};
}
