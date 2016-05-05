#pragma once

#include <string>

class DBAdapter
{
public:
	enum class LogLevel
	{
		Message,
		Warning,
		Error
	};
	virtual void Log(std::string msg, LogLevel = LogLevel::Message) = 0;
	
};

