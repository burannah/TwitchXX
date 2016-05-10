#pragma once

#include <string>
#include <cpprest/uri.h>
#include <cpprest/json.h>

namespace TwitchXX
{
	class MakeRequest
	{
	std::wstring _client_id;
	std::wstring _api_version;
	public:
	explicit MakeRequest(std::wstring apiString = L"", std::wstring clientId = L"" ) : _client_id(clientId),_api_version(apiString) {};
	virtual ~MakeRequest();
	web::json::value operator()(const web::uri& request) const;
	};
}

