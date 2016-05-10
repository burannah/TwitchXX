#pragma once
#include "DBAdapter.h"

#include <mongocxx\client.hpp>
#include <mongocxx\instance.hpp>
#include <memory>

namespace TwitchXX
{
	class MongoDB :
	public DBAdapter
	{
	std::unique_ptr<mongocxx::instance> _instance;
	std::unique_ptr<mongocxx::client> _client;
	public:
	MongoDB();
	MongoDB(MongoDB&& db);
	virtual ~MongoDB();

	mongocxx::database GetDb(const std::string& db_name) const;
	};
}
