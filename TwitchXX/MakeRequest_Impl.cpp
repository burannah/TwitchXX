//
// Created by buran on 17/04/18.
//

#include <MakeRequest_Impl.h>

#include <RequestParams.h>

namespace TwitchXX
{
/**
*****************************************************************************************
*  @brief      MakreRequest main method
*
*  @details      Performs request to Twitch service
*
*  @param      params MakeRequest::ReqiestParams object - request descriptor
*
*  @return     resposne parsed to web::json::value object. Null-json if return code != OK.
*			   Updates last status_code field.
****************************************************************************************/
    web::json::value MakeRequest_Impl::performRequest(const RequestParams &params)
    {
        web::http::client::http_client http_client("https://api.twitch.tv/", _config);
        web::http::http_request request(params.method);

        if(_client_id.length() > 0)request.headers().add("Client-ID", _client_id);
        if(params.scope != AuthScope::NO_SCOPE)
        {
            if(!_authToken)
            {
                std::stringstream ss;
                ss << "No auth token provided for " << params.uri.to_string() << " request";
                throw TwitchException(ss.str().c_str());
            }
            request.headers().add("Authorization", _authToken->get(params.scope));
        }
        request.set_request_uri({params.uri});
        request.headers().set_content_type("application/json");
        if (!params.body.is_null())
        {
            utility::stringstream_t ss;
            ss << params.body;
            request.set_body(ss.str());
            //request.headers().set_content_type(U("application/json"));
        }

        Log::Debug("Request: " + request.to_string());
        ucout << "Request: " << request.to_string() << "\n";

        pplx::task<web::json::value> task = http_client.request(request)
                .then([this](web::http::http_response response) -> pplx::task<web::json::value>
                      {
                          Log::Debug("Response: " + response.to_string());
                          Log::Info("Response status: " + response.status_code());
#ifdef _DEBUG
                          ucout << response.to_string() << "\n";
#endif
                          fetchHeaderParams(response.headers());
                          this->_last_status = response.status_code();
                          if (response.status_code() == web::http::status_codes::OK
                              || response.status_code() == web::http::status_codes::Accepted)
                          {
                              if (response.headers().content_type().find("json") == std::wstring::npos)
                              {
                                  return response.extract_json(true);
                              }


                              return response.extract_json();

                          }
                          else
                          {
                              auto error = response.extract_json().get();
                              utility::string_t msg;
                              if (!error.is_null())
                              {
                                  msg = error.at("error").as_string() + ": " + error.at("message").as_string();
                              }

                              throw TwitchException(msg, response.status_code());
                          }
                      });

        try
        {
            auto result = task.get();
            if (params.callback != nullptr)
            {
                params.callback(result);
            }
            return result;
        }
        catch (const std::exception& e)
        {
            Log::Error(std::string("Unknown exception: ") + e.what());
            printf("Error exception:%s\n", e.what());
            throw;
        }
    }
}
