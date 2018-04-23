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

    class Api
    {
    public:
        explicit Api(const options& opt = Request::initOptionsFromConfig());

        const Request& reqOnce() const
        {
            return _requestOnce;
        };

        const Request& reqWait() const
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
