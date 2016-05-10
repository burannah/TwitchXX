#pragma once

#include <string>

namespace TwitchXX
{
	class MongoLogger;

	class Logger
	{
	public:
	Logger() {};

	virtual ~Logger()
	{
	}

	enum class LogLevel
	{
	Message,
	Warning,
	Error
	};
	virtual void Log(std::wstring msg, LogLevel = LogLevel::Message) = 0;
	};

}
