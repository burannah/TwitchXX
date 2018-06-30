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
    /**
    ****************************************s*************************************************
    *  @brief      MakeRequest constructor
    *
    *  @details    Creates MakeRequest object.
    *1
    *  @param      options - string map containing request options. apiString api version string, ex. application/vnd.twitchtv.v3+json
    ****************************************************************************************/
    Request::Request(const std::shared_ptr<MakeRequest_Impl> &impl,
                     const std::shared_ptr<AuthToken> &token)
    :_request(impl)
    ,_auth_token(token)
    {

    }

    web::json::value Request::get(const web::uri &uri,
                                  AuthScope scope,
                                  Callback callback)
    {
        RequestParams params { uri,web::http::methods::GET,
                               web::json::value::null(),
                               std::move(callback),
                               scope,
                               _response_headers_params,
                               _auth_token};
        return performRequest(params);
    }

    web::json::value
    Request::put(const web::uri &uri,
                 AuthScope scope,
                 const web::json::value &body,
                 Callback callback)
    {
        return performRequest({uri,
                               web::http::methods::PUT,
                               body,
                               std::move(callback),
                               scope,
                               _response_headers_params,
                               _auth_token});
    }

    web::json::value
    Request::post(const web::uri &uri,
                  AuthScope scope,
                  const web::json::value &body,
                  Callback callback)
    {
        return performRequest({uri,
                               web::http::methods::POST,
                               body,
                               std::move(callback),
                               scope,
                               _response_headers_params,
                               _auth_token});
    }

    web::json::value Request::del(const web::uri &uri,
                                  AuthScope scope,
                                  Callback callback)
    {
        return performRequest({uri,
                               web::http::methods::DEL,
                               web::json::value::null(),
                               std::move(callback),
                               scope,
                               _response_headers_params,
                               _auth_token});
    }

    void Request::setAuthToken(const std::shared_ptr<AuthToken> &token)
    {
        _auth_token = token;
    }

    void Request::setResponseHeaderParam(const std::string &param)
    {
        _response_headers_params.insert(param);
    }

    const std::map<std::string, std::string>& Request::getResponseHeaderParams() const
    {
        return _response_headers;
    }

    web::http::status_code Request::statusCode() const
    {
        return _response_status_code;
    }

    void Request::clearResponseHeadersParams()
    {
        _response_headers_params.clear();
        Log::Debug("Response params cleared");
    }

    void Request::saveRequestResponse()
    {
        _response_headers  = _request->getResponseHeaderParams();
        _response_status_code = _request->statusCode();
    }
}

