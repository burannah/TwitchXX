#pragma once

#include <memory>
#include "DBAdapter.h"

class TwitchXX
{
	std::unique_ptr<DBAdapter> _db;
public:
	TwitchXX();
	~TwitchXX();
};

