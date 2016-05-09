#pragma once


namespace TwitchXX
{
	class DBAdapter
	{
	public:
		DBAdapter() {};
		DBAdapter(const DBAdapter& db) = delete;
		DBAdapter(DBAdapter&& db) {};

		virtual ~DBAdapter() {};


	};
	
}
