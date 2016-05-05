#pragma once
#include "DBAdapter.h"

#include <mongocxx\client.hpp>
#include <mongocxx\instance.hpp>

class MongoDB :
	public DBAdapter
{
	std::unique_ptr<mongocxx::instance> _instance;
	std::unique_ptr<mongocxx::client> _client;
public:
	MongoDB();
	virtual ~MongoDB();

	void Log(std::string msg, LogLevel level = LogLevel::Message);
};

