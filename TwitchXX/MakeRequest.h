#pragma once

#include <string>
#include <iostream>
#include <utility>
#include <memory>

#include <TwitchDef.h>
#include <MakeRequest_Impl.h>


namespace TwitchXX
{
    ///Class to perform a web request.
    class MakeRequest
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

		///MakerRequest constructor
		explicit MakeRequest(const std::map<utility::string_t,utility::string_t>& options /**< [in] Api-version string*/
                                                                                            );

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

		///Last request's status code
		web::http::status_code status_code() const { return _last_status; }

        ///Check connection
        bool CheckConnection();

        void setAuthToken(std::shared_ptr<AuthToken> token)
        {
            _authToken = token;
        }

		///Add a header param to be extracted from the response
		void setResponseHeaderParam(const std::string& param)
		{
			_response_header_params.insert(std::make_pair(param,""));
		}

		const auto& getResponseHeaderParams() const
        {
            return _response_header_params;
        }

    protected:


	private:
		utility::string_t _client_id;
		web::http::client::http_client_config _config;
		web::http::status_code _last_status;
		utility::string_t _token;
        std::shared_ptr<AuthToken> _authToken;
		std::map<std::string,std::string> _response_header_params;

		void SetupProxy(const std::map<utility::string_t, utility::string_t> &options);

        void fetchHeaderParams(web::http::http_headers &headers);
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

