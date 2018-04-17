#include <MakeRequest.h>

#include <StreamsOptions.h>
#include <stdexcept>

#include <TwitchException.h>
#include <Utility.h>
#include <Log.h>

namespace TwitchXX
{

	/**
	*****************************************************************************************
	*  @brief      MakeRequest setup proxy.
	*
	*  @details      SetupProxy() requires options to be defined and filled
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
	*  @details    Creates MakeRequest object.
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

	}

    /**
    *****************************************************************************************
    *  @brief      MakreRequest check connection
    *
    *  @details    Performs request to Twitch service to ensure that connection is OK
    *
    *  @return     true or false
    ****************************************************************************************/
    bool MakeRequest::CheckConnection()
    {
        auto response = this->get("games/top");
        return !response.is_null();
    }



    void MakeRequest::fetchHeaderParams(web::http::http_headers &headers)
    {
        std::for_each(_response_header_params.begin(), _response_header_params.end(), [&](auto& p)
        {
            if(headers.has(p.first))
            {
                p.second = headers[p.first];
            }
            else
            {
                p.second = "N/A";
            }
        });
    }

    /**
    *****************************************************************************************
    *  @brief      MakeRequest constructor
    *
    *  @details      Creates MakeRequest object.
    *1
    *  @param      options - string map containing request options. apiString api version string, ex. application/vnd.twitchtv.v3+json
    *  @param      clientId Client-id value
    *  @param	   token user's token. Some requests requires auth scope granted by user
    *			   If token is not set such requests will fail.
    ****************************************************************************************/

    options &MakeRequest::initOptionsFromConfig(const std::string &path)
    {
        auto & opt = getOptions();

        utility::ifstream_t options_file(!path.empty() ?  path.c_str() : "twitchxx.cfg");
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

		return opt;

    }

    web::json::value MakeRequest::get(const web::uri &uri, AuthScope scope, Callback callback)
    {
        RequestParams params { uri,web::http::methods::GET,
                               web::json::value::null(),
                               std::move(callback),
                               scope};
        return this->performRequest(params);
    }

    web::json::value
    MakeRequest::put(const web::uri &uri, AuthScope scope, const web::json::value &body, Callback callback)
    {
        return performRequest({ uri,
                                web::http::methods::PUT,
                                body,
                                std::move(callback),
                                scope});
    }

    web::json::value
    MakeRequest::post(const web::uri &uri, AuthScope scope, const web::json::value &body, Callback callback)
    {
        return performRequest({ uri,
                                web::http::methods::POST,
                                body,
                                std::move(callback),
                                scope});
    }

    web::json::value MakeRequest::del(const web::uri &uri, AuthScope scope, Callback callback)
    {
        return performRequest({uri,
                               web::http::methods::DEL,
                               web::json::value::null(),
                               std::move(callback),
                               scope});
    }
}
