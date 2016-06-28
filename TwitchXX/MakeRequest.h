#pragma once

#include <string>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include "Logger.h"

namespace TwitchXX
{
	///Global object options should be defined and filled with values (for proxy parameters e.t.c.)
	extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;
	///Global logger
	extern std::shared_ptr<Logger> Log;

	class MakeRequest
	{
	public:

		///MakerRequest constructor
		explicit MakeRequest(std::wstring apiString = L"", /**< [in] Api-version string*/ 
							 std::wstring clientId = L"", /**< [in] Client-id stirng*/
							 std::wstring token= L"" /**< [in] User's auth token*/);

		///MakeRequest destructor
		virtual ~MakeRequest() {};
		///Default copy assigment operator.
		MakeRequest& operator=(const MakeRequest&) = default;
		///Default move assigment operator.
		MakeRequest& operator=(MakeRequest&&) = default;

		///MakeRequest's main method.
		web::json::value operator()(const web::uri& uri,/**< [in] request's uri (parameters and options)*/ 
									const web::http::method& method = web::http::methods::GET, /**< [in] request method*/
									web::json::value body = web::json::value() /**< [in] requests body for put and post methods */);
		///Last request's status code
		web::http::status_code status_code() const { return _last_status; }

	private:
		std::wstring _client_id;
		std::wstring _api_version;
		web::http::client::http_client_config _config;
		web::http::status_code _last_status;
		std::wstring _token;

		void SetupProxy();
	};
}

