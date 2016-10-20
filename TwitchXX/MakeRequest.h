#pragma once

#include <string>
#include <iostream>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/details/basic_types.h> //TODO: CPPRESTSDK dependency
#include "Logger.h"



namespace TwitchXX
{

	class value;
	using Callback = std::function<void(const web::json::value&)>;

	///Global logger
	extern std::shared_ptr<Logger> Log;

    class MakeRequest
	{
	public:
		struct RequestParams
		{
			web::uri uri;										///< Request uri
			web::http::method method = web::http::methods::GET; ///< Method
			web::json::value body;								///< Request's body. Used for sending form's parameters for example
			std::function<void(const web::json::value&)> callback;	///< Callback function to be executed on request's result 

			RequestParams() :method(web::http::methods::GET) {};
			RequestParams(const web::uri& uri, web::http::method method, const web::json::value& body, std::function<void(const web::json::value&)> callback) :uri(uri), method(method), body(body), callback(callback) {};
		};

		///MakerRequest constructor
		explicit MakeRequest(const std::map<utility::string_t,utility::string_t>& options /**< [in] Api-version string*/
                                                                                            );

		/// MakeRequest destructor
		virtual ~MakeRequest() {};
        /// Default copy constructor
        MakeRequest(const MakeRequest&) = default;
		/// Default copy assigment operator.
		MakeRequest& operator=(const MakeRequest&) = default;
        /// Default move constructor
        MakeRequest(MakeRequest&&) = default;
		/// Default move assigment operator.
		MakeRequest& operator=(MakeRequest&&) = default;


		///Perform get request
		web::json::value get(const web::uri& uri, Callback callback = Callback()) const
		{
			return (*this)({ uri,web::http::methods::GET,web::json::value::null(),callback });
		}

		///Perform put request
		web::json::value put(const web::uri& uri,const web::json::value& body = web::json::value::null(),Callback callback = Callback() ) const
		{
			return (*this)({ uri,web::http::methods::PUT,body,callback });
		}

		///Perform post request
		web::json::value post(const web::uri& uri, const web::json::value& body = web::json::value::null(), Callback callback = Callback()) const
		{
			return (*this)({ uri,web::http::methods::POST,body,callback });
		}

		///Perform delete request
		web::json::value del(const web::uri& uri, Callback callback = Callback()) const
		{
			return (*this)({ uri,web::http::methods::DEL,web::json::value::null(),callback });
		}

		///Last request's status code
		web::http::status_code status_code() const { return _last_status; }

	private:
		utility::string_t _client_id;
		utility::string_t _api_version;
		web::http::client::http_client_config _config;
		mutable web::http::status_code _last_status;
		utility::string_t _token;

		void SetupProxy(const std::map<utility::string_t, utility::string_t> &options);

		///MakeRequest's main method.
		///@param	params request parameters descriptor
		///@return	response parsed to web::json::value object. Null json value if HTTP result code != OK.
		web::json::value operator()(const RequestParams params) const;
		///Deprecated version of the request
		///@param      uri request parameters
		///@param      method request method type(GET by default)
		///@param      body request body for post and put requests
		///@return     resposne parsed to web::json::value object.Null - json if return code != OK.
		web::json::value operator()(const web::uri& uri,/**< [in] request's uri (parameters and options)*/
			const web::http::method& method = web::http::methods::GET, /**< [in] request method*/
			web::json::value body = web::json::value()/**< [in] requests body for put and post methods */) const//TODO: By value?!
		{
			return (*this)({ uri,method,body,Callback() });;
		}
	};
}

