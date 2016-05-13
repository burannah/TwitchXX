#pragma once

#include <string>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>

namespace TwitchXX
{
	class MakeRequest
	{
		std::wstring _client_id;
		std::wstring _api_version;
		web::http::client::http_client_config _config;
	public:
		void SetupProxy();
		explicit MakeRequest(std::wstring apiString = L"", std::wstring clientId = L"");;
		virtual ~MakeRequest();
		web::json::value operator()(const web::uri& request) const;
	};
}

