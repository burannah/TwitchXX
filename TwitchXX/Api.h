//
// Created by buran on 12/03/18.
//

#ifndef TWITCHXX_API_H
#define TWITCHXX_API_H

#include <memory>

#include <RequestOnce.h>
#include <RequestWait.h>

namespace TwitchXX
{
    class UserAccessToken;
    class MakeRequest_Impl;
    class UserAccessToken;

    /// Main API class incapsulating access tokens and requests
    class Api
    {
    public:
        /// Construct Api object out of options map
        explicit Api(const options& opt = Request::initOptionsFromConfig());

        /// Get non-waitng request object (will throw TwitchException with CODE=429 - TOO MANY REQUESTS)
        RequestOnce reqOnce() const
        {
            return _requestOnce;
        }

        /// Get waiting request object (will wait for next time frame upon reaching the threshold)
        RequestWait reqWait() const
        {
            return _requestWait;
        }

    private:
        std::shared_ptr<MakeRequest_Impl> _requestImpl;
        std::shared_ptr<UserAccessToken> _userToken;
        RequestOnce _requestOnce;
        RequestWait _requestWait;
    };
}


#endif //TWITCHXX_API_H
