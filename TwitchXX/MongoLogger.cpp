#include "MongoLogger.h"
#include <ctime>
#include <chrono>
#include <mongocxx/database.hpp>
#include "MongoDB.h"
#include <locale>
#include <codecvt>

TwitchXX::MongoLogger::MongoLogger()
{
	MongoDB mongoDb;
	_db = std::make_shared<mongocxx::database>(mongoDb.GetDb(DatabaseName));
}

TwitchXX::MongoLogger::MongoLogger(const MongoLogger& log) :
	_db(log._db)
{

}

TwitchXX::MongoLogger::MongoLogger(MongoLogger&& log):
	_db(std::move(_db))
{

}

TwitchXX::MongoLogger::MongoLogger(const std::shared_ptr<mongocxx::database>& db) :
	_db(db)
{

}

TwitchXX::MongoLogger::MongoLogger(mongocxx::database db) :
	_db(std::make_shared<mongocxx::database>(std::move(db)))
{
}

TwitchXX::MongoLogger::~MongoLogger()
{
}

void TwitchXX::MongoLogger::Log(std::wstring msg, LogLevel level)
{
#ifndef _DEBUG
	//Omit debug loggin in non-debug build
	if (level == LogLevel::Debug) return;
#endif
	auto log_collection = (*_db)["Log"];
	bsoncxx::builder::stream::document log_msg{};

	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buff[256];
	ctime_s(buff, 256, &now);
	std::wstring_convert<std::codecvt_utf8<wchar_t>> convertor;
	log_msg << "Datetime" << buff;
	log_msg << "Message" << convertor.to_bytes(msg);
	log_msg << "Severety" << static_cast<int>(level);
	log_collection.insert_one(log_msg.view());
}

