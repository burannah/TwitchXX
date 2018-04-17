//
// Created by buran on 17/04/18.
//

#include <WaitRequest_Impl.h>

#include <thread>

#include <TwitchException.h>
#include <Log.h>

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

    web::json::value WaitRequest_Impl::performRequest(const RequestParams &params)
    {
        auto impl = std::make_unique<MakeRequest_Impl>();
        while(true)
        {
            try
            {
                return impl->performRequest(params);
            }
            catch(const TwitchXX::TwitchException& e)
            {
                if(e.code() == 429) //Too many request
                {
                    Log::Debug("Request to: " + params.uri.to_string() + " has hit the rate limit.");
                    sleepForNextWindow(impl->getResponseHeaderParams());
                    continue;
                }
                throw;
            }

        }
    }
}

