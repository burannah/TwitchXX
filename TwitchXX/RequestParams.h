//
// Created by buran on 17/04/18.
//

#ifndef TWITCHXX_REQUESTPARAMS_H
#define TWITCHXX_REQUESTPARAMS_H

#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/details/basic_types.h> //TODO: CPPRESTSDK dependency
#include <Auth/AuthToken.h>

namespace TwitchXX
{
    ///Request params descriptor
    struct RequestParams
    {
        web::uri                                     uri;		                       ///< Request uri
        web::http::method                            method = web::http::methods::GET; ///< Method
        web::json::value                             body;							   ///< Request's body. Used for sending form's parameters for example
        std::function<void(const web::json::value&)> callback;	                       ///< Callback function to be executed on request's result
        AuthScope                                    scope = AuthScope::NO_SCOPE;      ///< Required authentication scope

        RequestParams() = default;
        RequestParams(web::uri uri,
                      web::http::method method,
                      web::json::value body,
                      std::function<void(const web::json::value &)> callback,
                      AuthScope scope)
                :uri(std::move(uri))
                , method(std::move(method))
                , body(std::move(body))
                , callback(std::move(callback))
                , scope(scope){};
    };
}


#endif //TWITCHXX_REQUESTPARAMS_H
