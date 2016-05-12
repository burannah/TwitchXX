#include "MakeRequest.h"
#include <cpprest/http_client.h>

namespace TwitchXX
{
	extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;
}


TwitchXX::MakeRequest::MakeRequest(std::wstring apiString, std::wstring clientId): 
	_client_id(clientId),
	_api_version(apiString)
{
	//Check global Options object for proxy settings;
	if(Options->find(U("proxy")) != Options->end())
	{
		web::web_proxy proxy((*Options)[U("proxy")]);
		//Check that both login and password were found in the options.
		if(Options->find(U("proxy_user")) != Options->find(U("proxy_password")))
		{
			web::credentials creds((*Options)[U("proxy_user")], (*Options)[U("proxy_password")]);
			proxy.set_credentials(creds);
			//_config.set_credentials(creds);
		}
		//_config.set_proxy(proxy);
	}
}

TwitchXX::MakeRequest::~MakeRequest()
{

}

web::json::value TwitchXX::MakeRequest::operator()(const web::uri& uri) const
{
	web::http::client::http_client http_client(U("https://api.twitch.tv/kraken"),_config);
	web::http::http_request request(web::http::methods::GET);

	if(_api_version.length()) request.headers().add(L"Accept", _api_version);
	if(_client_id.length())request.headers().add(L"Client-ID", _client_id);
	request.set_request_uri(uri);

	pplx::task<web::json::value> task = http_client.request(request)
		.then([](web::http::http_response response) -> pplx::task<web::json::value>
	{
		std::wostringstream stream;
		stream.str(std::wstring());
		stream << L"Content type: " << response.headers().content_type() << std::endl;
		stream << L"Content length: " << response.headers().content_length() << L"bytes" << std::endl;
		std::wcout << stream.str();
		if (response.status_code() == web::http::status_codes::OK)
		{
			return response.extract_json();
		}
		else
		{
			return pplx::task_from_result(web::json::value());
		}
	});

	try
	{
		return task.get();
	}
	catch (const std::exception &e)
	{
		printf("Error exception:%s\n", e.what());
	}

	return web::json::value();
}


