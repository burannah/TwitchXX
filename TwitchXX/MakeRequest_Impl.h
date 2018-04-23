//
// Created by buran on 17/04/18.
//

#ifndef TWITCHXX_MAKEREQUEST_IMPL_H
#define TWITCHXX_MAKEREQUEST_IMPL_H

#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <TwitchDef.h>

namespace TwitchXX
{

    class RequestParams;
    class AuthToken;

    class MakeRequest_Impl
    {
        public:
            std::mutex _lock;

            explicit MakeRequest_Impl(const options& opt);

            void setAuthToken(const std::shared_ptr<AuthToken>& token)
            {
                _authToken = token;
            }


        ///MakeRequest's main method.
            ///@param	params request parameters descriptor
            ///@return	response parsed to web::json::value object. Null json value if HTTP result code != OK.
            virtual web::json::value performRequest(const RequestParams &params);


        ///Add a header param to be extracted from the response
        void setResponseHeaderParam(const std::string& param)
        {
            _response_header_params.insert(std::make_pair(param,""));
        }

        const auto& getResponseHeaderParams() const
        {
            return _response_header_params;
        }

        ///Last request's status code
        web::http::status_code status_code() const { return _last_status; }

    private:
        std::shared_ptr<AuthToken> _authToken;
        web::http::client::http_client_config _config;
        std::map<std::string,std::string> _response_header_params;
        std::string _client_id;
        web::http::status_code _last_status;

        void fetchHeaderParams(web::http::http_headers &headers);
        void SetupProxy(const std::map<utility::string_t, utility::string_t> &options);
    };
}


#endif //TWITCHXX_MAKEREQUEST_IMPL_H
