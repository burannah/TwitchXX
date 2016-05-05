#include "MongoDB.h"



MongoDB::MongoDB():
	_instance{ std::make_unique<mongocxx::instance>()},
	_client{ std::make_unique<mongocxx::client>(mongocxx::uri{},mongocxx::options::client()) }
{
}


MongoDB::~MongoDB()
{
}

void MongoDB::Log(std::string msg, LogLevel level)
{
	auto log_collection = (*_client)["TwitchSpy"]["Log"];
	bsoncxx::builder::stream::document log_msg{};

	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	log_msg << "Datetime" << std::ctime(&now);
	log_msg << "Message" << msg;
	log_msg << "Severety" << static_cast<int>(level);
	log_collection.insert_one(log_msg.view());
}
