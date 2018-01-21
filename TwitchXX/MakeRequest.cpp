#include <stdexcept>

#include "MakeRequest.h"
#include "TwitchException.h"
#include "Property.h"
#include "Utility.h"

namespace TwitchXX
{

	/**
	*****************************************************************************************
	*  @brief      MakreRequest setup proxy. 
	*
	*  @usage      SetupProxy() requires options to be defined and filled
	*			   with values (proxy & proxy_password).
	*			   Note: Proxy host must starts with connection scheme (i.e. http,https etc).
	*  @param      options options dictionary (must contain proxy and/or proxy_password)
	*              proxy hostname shoudl start with a scheme - http, https etc.
	*
	*  @return     throws std::runtime_error if proxy settings not present in Options
	****************************************************************************************/
    void MakeRequest::SetupProxy(const std::map<utility::string_t, utility::string_t> &options)
	{
		//Check global Options object for proxy settings;
		if (options.find("proxy") != options.end())
		{
			web::web_proxy proxy(options.at("proxy"));
			//Check that both login and password were found in the options.
			if (options.find("proxy_user") != options.find("proxy_password"))
			{
				web::credentials creds(options.at("proxy_user"), options.at("proxy_password"));
				proxy.set_credentials(creds);
			}
			_config.set_proxy(proxy);
		}
	}

	/**
	****************************************s*************************************************
	*  @brief      MakeRequest constructor
	*
	*  @usage      Creates MakeRequest object. 
	*1
	*  @param      options - string map containing request options. apiString api version string, ex. application/vnd.twitchtv.v3+json
	*  @param      clientId Client-id value
	*  @param	   token user's token. Some requests requires auth scope granted by user
	*			   If token is not set such requests will fail.
	****************************************************************************************/
	MakeRequest::MakeRequest(const std::map<utility::string_t,utility::string_t>& options)
	{
        try
        {
            _client_id = options.at("api_key");
            _token = options.at("token");
        }
        catch (const std::out_of_range&)
        {
            utility::stringstream_t ss;
            ss << __FUNCTION__ << ": Not enough parameters!"
               << " api_key=" << _client_id
               << " token=" << _token;
            throw std::invalid_argument(ss.str());
        }

        SetupProxy(options);

        auto response = this->operator()("games/top");
        if (response.is_null())
        {
            throw TwitchException("Got empty response");
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

	web::json::value MakeRequest::operator()(const RequestParams &params) const
	{
		web::http::client::http_client http_client("https://api.twitch.tv/helix", _config);
		web::http::http_request request(params.method);

		if (_client_id.length() > 0)request.headers().add("Client-ID", _client_id);
		if (_token.length() > 6)request.headers().add("Authorization", "Bearer " + _token);
		request.set_request_uri({params.uri});
        request.headers().set_content_type("application/json");
		if (!params.body.is_null())
		{
			utility::stringstream_t ss;
			ss << params.body;
			request.set_body(ss.str());
			//request.headers().set_content_type(U("application/json"));
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
				if (response.headers().content_type().find("json") == std::wstring::npos)
				{
					return response.extract_json(true);
				}


				return response.extract_json();

			}
			else
			{
				auto error = response.extract_json().get();
				Property<utility::string_t, std::string> msg;
				if (!error.is_null())
				{
					msg.Set(error.at("error").as_string() + ": " + error.at("message").as_string());
				}
				else
				{
					msg.Set(""); //No error text in response
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

    /**
    ****************************************s*************************************************
    *  @brief      MakeRequest constructor
    *
    *  @usage      Creates MakeRequest object.
    *1
    *  @param      options - string map containing request options. apiString api version string, ex. application/vnd.twitchtv.v3+json
    *  @param      clientId Client-id value
    *  @param	   token user's token. Some requests requires auth scope granted by user
    *			   If token is not set such requests will fail.
    ****************************************************************************************/

    options &MakeRequest::initOptionsFromConfig(const std::string &path)
    {
        auto & opt = getOptions();

        utility::ifstream_t options_file(!path.empty() ?  path : "twitchxx.cfg");
        utility::string_t line;
        while(std::getline(options_file,line))
        {
            utility::stringstream_t iss(line);
            utility::string_t name, value;
            std::getline(iss, name, '=');
            std::getline(iss, value);
            if(name[0] == '#')
            {
                //Skip comments
                continue;
            }
            trim(name);
            trim(value);
			opt.insert({name, value});
        }

    }
}
