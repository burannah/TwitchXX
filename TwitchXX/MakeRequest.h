#pragma once

#include <string>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include "Logger.h"

namespace TwitchXX
{
	extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;
	extern std::shared_ptr<Logger> Log;

	class MakeRequest
	{
		std::wstring _client_id;
		std::wstring _api_version;
		web::http::client::http_client_config _config;
	public:
		void SetupProxy();

		explicit MakeRequest(std::wstring apiString = L"", std::wstring clientId = L"");

		virtual ~MakeRequest() {};

		web::json::value operator()(const web::uri& uri) const;
	};
}

