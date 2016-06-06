#include "MongoDB.h"



TwitchXX::MongoDB::MongoDB():
	_instance{ std::make_unique<mongocxx::instance>()},
	_client{ std::make_unique<mongocxx::client>(mongocxx::uri{},mongocxx::options::client()) }
{

}

TwitchXX::MongoDB::MongoDB(MongoDB&& db):
	_instance(std::move(db._instance)),
	_client(std::move(db._client))
{
}

TwitchXX::MongoDB::~MongoDB()
{
}

mongocxx::database TwitchXX::MongoDB::GetDb(const std::string& db_name) const
{
	return (*_client)[db_name];
}
