//
// Created by buran on 22/04/18.
//

#ifndef TWITCHXX_REQUEST_H
#define TWITCHXX_REQUEST_H

#include <cpprest/json.h>
#include <memory>

#include <TwitchDef.h>
#include <cpprest/uri.h>
#include <cpprest/http_msg.h>
#include <cpprest/http_client.h>
#include <Auth/AuthToken.h>


namespace TwitchXX
{
    class RequestParams;
    class MakeRequest_Impl;

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
                             Callback callback = Callback()) const;

        ///Perform put request
        web::json::value put(const web::uri& uri,
                             AuthScope scope = AuthScope::NO_SCOPE,
                             const web::json::value& body = web::json::value::null(),
                             Callback callback = Callback() ) const;

        ///Perform post request
        web::json::value post(const web::uri& uri,
                              AuthScope scope = AuthScope::NO_SCOPE,
                              const web::json::value& body = web::json::value::null(),
                              Callback callback = Callback()) const;

        ///Perform delete request
        web::json::value del(const web::uri& uri,
                             AuthScope scope = AuthScope::NO_SCOPE,
                             Callback callback = Callback()) const;


        ///Add a header param to be extracted from the response
        void setResponseHeaderParam(const std::string &param);

        ///Get response headers params
        const std::map<std::string, std::string> & getResponseHeaderParams() const;

        ///Clear all response header params
        void clearResponseHeadersParams();

        ///Last request's status code
        web::http::status_code status_code() const;

        void setAuthToken(std::shared_ptr<AuthToken> token)const;

    protected:
        std::shared_ptr<MakeRequest_Impl> _request;
        std::set<std::string>             _response_headers_params;

        /// Protected constructor. This object should not be called directly
        explicit Request(const std::map<utility::string_t, utility::string_t> &options,
                         const std::shared_ptr<MakeRequest_Impl> &impl);

        ///MakeRequest's main method.
        ///@param	params request parameters descriptor
        ///@return	response parsed to web::json::value object. Null json value if HTTP result code != OK.
        virtual web::json::value performRequest(const RequestParams &params) const = 0;
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
