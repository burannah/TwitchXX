#include "MakeRequest.h"
#include "TwitchException.h"
#include "Property.h"

#define out std::cout;
namespace TwitchXX
{

	/**
	*****************************************************************************************
	*  @brief      MakreRequest setup proxy. 
	*
	*  @usage      SetupProxy() requires global object Options to be defined and filled 
	*			   with values (proxy & proxy_password).
	*			   Note: Proxy host must starts with connection scheme (i.e. http,https etc).
	*
	*  @return     throws std::runtime_error if proxy settings not present in Options
	****************************************************************************************/
	void MakeRequest::SetupProxy()
	{
		//Check global Options object for proxy settings;
		if (TwitchXX::Options->find(U("proxy")) != TwitchXX::Options->end())
		{
			web::web_proxy proxy((*TwitchXX::Options)[U("proxy")]);
			//Check that both login and password were found in the options.
			if (TwitchXX::Options->find(U("proxy_user")) != TwitchXX::Options->find(U("proxy_password")))
			{
				web::credentials creds((*TwitchXX::Options)[U("proxy_user")], (*TwitchXX::Options)[U("proxy_password")]);
				proxy.set_credentials(creds);
			}
			_config.set_proxy(proxy);
		}
		else
		{
			throw std::runtime_error("No proxy has been set");
		}
	}

	/**
	*****************************************************************************************
	*  @brief      MakeRequest constructor
	*
	*  @usage      Creates MakeRequest object. 
	*			   Note: For now Twich allows to perform requests without client id.
	*			   But soon it wont be possible. Take care.
	*
	*  @param      apiString api version string, ex. application/vnd.twitchtv.v3+json
	*  @param      clientId Client-id value
	*  @param	   token user's token. Some requests requires auth scope granted by user
	*			   If token is not set such requests will fail.
	****************************************************************************************/
	MakeRequest::MakeRequest(const utility::string_t& apiString,const utility::string_t& clientId, const utility::string_t& token)
		: _client_id(clientId), 
		_api_version(apiString),
		_token(U("OAuth ") + token)
	{
		try
		{
			//Making a "naked" request to check if we need to use proxy
			auto response = this->operator()(U(""));
			if (!response.is_null())
			{
				//Got resposne from Tiwtch. Nothing to do here anymore
				return;
			}
		}
		catch (std::exception& e)
		{
			utility::stringstream_t s;
			s << "Direct connection failed with: \"" << e.what() << "\". Trying to connect though proxy" << std::endl;
			TwitchXX::Log->Log(s.str(), Logger::LogLevel::Warning);
		}
		SetupProxy();
		try
		{
			auto response = this->operator()(U(""));
			if (!response.is_null())
			{
				//Got resposne from Tiwtch. Nothing to do here anymore
				return;
			}
		}
		catch (std::exception& e)
		{
			utility::stringstream_t s;
			s << "Connect through proxy has failed either: \"" << e.what() << "\". " << std::endl;
			Log->Log(s.str(), Logger::LogLevel::Error);
			throw;
		}
	}


	/**
	*****************************************************************************************
	*  @brief      MakreRequest main method
	*
	*  @usage      Performs request to Twitch service
	*
	*  @param      params MakeRequest::ReqiestParams object - request descriptor
	*
	*  @return     resposne parsed to web::json::value object. Null-json if return code != OK.
	*			   Updates last status_code field.
	****************************************************************************************/

	web::json::value MakeRequest::operator()(const RequestParams params)
	{
		web::http::client::http_client http_client(U("https://api.twitch.tv/kraken"), _config);
		web::http::http_request request(params.method);

		if (_api_version.length()) request.headers().add(U("Accept"), _api_version);
		if (_client_id.length())request.headers().add(U("Client-ID"), _client_id);
		if (_token.length() > 6)request.headers().add(U("Authorization"), _token);
		request.set_request_uri(params.uri);
		if (!params.body.is_null())
		{
			utility::stringstream_t ss;
			ss << params.body;
			request.set_body(ss.str());
			request.headers().set_content_type(U("application/json"));
		}

		ucout << "Request: " << request.to_string() << "\n";

		pplx::task<web::json::value> task = http_client.request(request)
			.then([this](web::http::http_response response) -> pplx::task<web::json::value>
		{
#ifdef _DEBUG
			ucout << response.to_string() << U("\n");
#endif
			this->_last_status = response.status_code();
			if (response.status_code() == web::http::status_codes::OK)
			{
				if (response.headers().content_type().find(U("json")) == std::wstring::npos)
				{
					return response.extract_json(true);
				}
				else
				{
					return response.extract_json();
				}
			}
			else
			{
				auto error = response.extract_json().get();
				Property<utility::string_t, std::string> msg;
				if (!error.is_null())
				{
					msg.Set(error.at(U("error")).as_string() + U(": ") + error.at(U("message")).as_string());
				}
				else
				{
					msg.Set(U("")); //No error text in response
				}

				throw TwitchException(msg.to_string(), response.status_code());
			}
		});

		try
		{
			auto result = task.get();
			if (params.callback != nullptr)
			{
				params.callback(result);
			}
			return result;
		}
		catch (const std::exception& e)
		{
			printf("Error exception:%s\n", e.what());
			throw;
		}

	}
}
