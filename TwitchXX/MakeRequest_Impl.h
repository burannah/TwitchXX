//
// Created by buran on 17/04/18.
//

#ifndef TWITCHXX_MAKEREQUEST_IMPL_H
#define TWITCHXX_MAKEREQUEST_IMPL_H

#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <TwitchDef.h>
#include <Log.h>
namespace TwitchXX
{

    class RequestParams;
    class AuthToken;

    /// Make request implementation class
    /// This is where real HTTP request happens
    class MakeRequest_Impl
    {
        public:
            std::mutex _lock; ///< Request sync mutex

            ///Constructor
            explicit MakeRequest_Impl(const options& opt);

            ///MakeRequest's main method.
            ///@param	params request parameters descriptor
            ///@return	response parsed to web::json::value object. Null json value if HTTP result code != OK.
            virtual web::json::value performRequest(const RequestParams &params);


            ///Get headers values for last performed request
            const auto& getResponseHeaderParams() const
            {
                return _response_header_params;
            }

            ///Last request's status code
            web::http::status_code statusCode() const { return _last_status; }

    private:
        web::http::client::http_client_config _config;
        std::map<std::string,std::string> _response_header_params;
        std::string _client_id;
        web::http::status_code _last_status;
        std::string _base_url;

        void fetchHeaderParams(web::http::http_headers &headers);
        void setupProxy(const std::map<utility::string_t, utility::string_t> &options);
    };
}


#endif //TWITCHXX_MAKEREQUEST_IMPL_H
