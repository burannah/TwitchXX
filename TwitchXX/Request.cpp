//
// Created by buran on 22/04/18.
//

#include <Request.h>
#include <cpprest/http_msg.h>
#include <Utility.h>
#include <RequestParams.h>
#include <MakeRequest_Impl.h>

namespace TwitchXX
{
    options& Request::initOptionsFromConfig(const std::string &path)
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

    /**
    ****************************************s*************************************************
    *  @brief      MakeRequest constructor
    *
    *  @details    Creates MakeRequest object.
    *1
    *  @param      options - string map containing request options. apiString api version string, ex. application/vnd.twitchtv.v3+json
    ****************************************************************************************/
    Request::Request(const std::map<utility::string_t, utility::string_t> &options,
                     const std::shared_ptr<MakeRequest_Impl> &impl)
    :_request(impl)
    {

    }

    web::json::value Request::get(const web::uri &uri,
                                  AuthScope scope,
                                  Callback callback) const
    {
        RequestParams params { uri,web::http::methods::GET,
                               web::json::value::null(),
                               std::move(callback),
                               scope};
        return performRequest(params);
    }

    web::json::value
    Request::put(const web::uri &uri,
                 AuthScope scope,
                 const web::json::value &body,
                 Callback callback) const
    {
        return performRequest({ uri,
                                web::http::methods::PUT,
                                body,
                                std::move(callback),
                                scope});
    }

    web::json::value
    Request::post(const web::uri &uri,
                  AuthScope scope,
                  const web::json::value &body,
                  Callback callback) const
    {
        return performRequest({ uri,
                                web::http::methods::POST,
                                body,
                                std::move(callback),
                                scope});
    }

    web::json::value Request::del(const web::uri &uri,
                                  AuthScope scope,
                                  Callback callback) const
    {
        return performRequest({ uri,
                                web::http::methods::DEL,
                                web::json::value::null(),
                                std::move(callback),
                                scope});
    }

    void Request::setAuthToken(std::shared_ptr<AuthToken> token) const
    {
        _request->setAuthToken(token);
    }

    void Request::setResponseHeaderParam(const std::string &param) const
    {
        _request->setResponseHeaderParam(param);
    }

    const std::map<std::string, std::string>& Request::getResponseHeaderParams() const
    {
        return _request->getResponseHeaderParams();
    }

    web::http::status_code Request::status_code() const
    {
        return _request->status_code();
    }
}

