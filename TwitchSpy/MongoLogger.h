#pragma once
#include "Logger.h"
#include <memory>
#include <mongocxx/options/aggregate.hpp>

namespace TwitchXX
{
	extern std::string DatabaseName;

	class MongoDB;

	class MongoLogger : public Logger
	{
		std::shared_ptr<mongocxx::database> _db;
	public:

		MongoLogger();
		MongoLogger(const MongoLogger& log);
		MongoLogger(MongoLogger&& log);
		explicit MongoLogger(const std::shared_ptr<mongocxx::database>& db);
		explicit MongoLogger(mongocxx::database db);

		virtual ~MongoLogger();

		void Log(std::wstring msg, LogLevel = LogLevel::Message) const override;
	};
}
