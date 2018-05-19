//
// Created by buran on 22/04/18.
//

#ifndef TWITCHXX_REQUEST_H
#define TWITCHXX_REQUEST_H

#include <cpprest/json.h>
#include <memory>

#include <TwitchDef.h>
#include <Auth/AuthToken.h>

#include <cpprest/http_msg.h>
#include <cpprest/http_client.h>

namespace web { class uri; }

namespace TwitchXX
{
    class RequestParams;
    class MakeRequest_Impl;
    class AuthToken;


    /// Abstract request class. Contains general logic
    class Request
    {
    public:
        ///Callback handler type for all request methods (post,get,del,put)
        using Callback = std::function<void(const web::json::value&)>;

        ///Global request parameters holder
        static options& getOptions()
        {
            static options opt;
            return opt;
        }

        ///Init request options by default config
        static options& initOptionsFromConfig(const std::string& path = std::string());


        ///Perform get request
        web::json::value get(const web::uri& uri,
                             AuthScope scope = AuthScope::NO_SCOPE,
                             Callback callback = Callback());

        ///Perform put request
        web::json::value put(const web::uri& uri,
                             AuthScope scope = AuthScope::NO_SCOPE,
                             const web::json::value& body = web::json::value::null(),
                             Callback callback = Callback() );

        ///Perform post request
        web::json::value post(const web::uri& uri,
                              AuthScope scope = AuthScope::NO_SCOPE,
                              const web::json::value& body = web::json::value::null(),
                              Callback callback = Callback());

        ///Perform delete request
        web::json::value del(const web::uri& uri,
                             AuthScope scope = AuthScope::NO_SCOPE,
                             Callback callback = Callback());


        ///Add a header param to be extracted from the response
        void setResponseHeaderParam(const std::string &param);

        ///Get response headers params
        const std::map<std::string, std::string> & getResponseHeaderParams() const;

        ///Clear all response header params
        void clearResponseHeadersParams();

        ///Last request's status code
        web::http::status_code statusCode() const;

        /// Set authorization token to use by this request instance
        void setAuthToken(const std::shared_ptr<AuthToken> &token);

    protected:
        std::shared_ptr<MakeRequest_Impl>  _request;
        std::set<std::string>              _response_headers_params;
        std::map<std::string, std::string> _response_headers;
        web::http::status_code             _response_status_code;
        std::shared_ptr<AuthToken>         _auth_token;

        /// Protected constructor. This object should not be called directly
        explicit Request(const std::map<utility::string_t, utility::string_t> &options,
                         const std::shared_ptr<MakeRequest_Impl> &impl);

        /// Abstract function to be called from all request type methods: GET, POST, PUT, DEL
        /// Should be implemented by derived class for pre processing of RequestParams object
        virtual web::json::value performRequest(const RequestParams &params) = 0;

        void saveRequestResponse();
    };

    template<typename T>
    void addRangeOfParamsToBuilder(web::uri_builder& builder, const std::__cxx11::string& name, std::vector<T> c)
    {
        for(const auto& element: c)
        {
            builder.append_query(name, element);
        }
    }
}




#endif //TWITCHXX_REQUEST_H
