//
// Created by buran on 17/04/18.
//

#include <RequestWait.h>

#include <thread>

#include <TwitchException.h>
#include <Log.h>
#include <MakeRequest_Impl.h>
#include <RequestParams.h>

namespace TwitchXX
{
    namespace
    {
        const std::string RATE_LIMIT_RESET = "RateLimit-Reset";

        void sleepForNextWindow(const std::map<std::string,std::string>& params)
        {
            auto unixTimeString = params.at(RATE_LIMIT_RESET);
            long int unixTime = 0;
            try
            {
                unixTime = std::stol(unixTimeString);
            }
            catch(...)
            {
                Log::Error("Unable to parse header RateLimit-Reset param: " + unixTimeString);
                return;
            }
            auto time = static_cast<std::time_t>(unixTime);
            std::this_thread::sleep_until(std::chrono::system_clock::from_time_t(time));
        }
    }

    web::json::value RequestWait::performRequest(const RequestParams &params)
    {
        std::lock_guard<std::mutex> lock(_request->_lock);
        while(true)
        {
            try
            {
                auto params_copy{params};
                params_copy.responseHeadersParams.insert(_response_headers_params.begin(),
                                                         _response_headers_params.end());
                auto response = _request->performRequest(params_copy);
                saveRequestResponse();
                return response;
            }
            catch(const TwitchXX::TwitchException& e)
            {
                if(e.code() == web::http::status_codes::TooManyRequests) //Too many request
                {
                    Log::Debug("Request to: " + params.uri.to_string() + " has hit the rate limit.");
                    saveRequestResponse();
                    sleepForNextWindow(getResponseHeaderParams());
                    continue;
                }
                throw;
            }

        }
    }

    RequestWait::RequestWait(const std::shared_ptr<MakeRequest_Impl> &impl,
                             const std::shared_ptr<AuthToken> &token)
    : Request(impl, token)
    {
        _response_headers_params.insert(RATE_LIMIT_RESET);
    }
}

