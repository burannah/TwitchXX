//
// Created by buran on 12/03/18.
//

#ifndef TWITCHXX_API_H
#define TWITCHXX_API_H

#include <memory>
#include <MakeRequest.h>
#include <UserFollows.h>

namespace TwitchXX
{
    class MakeRequest;
    class UserAccessToken;

    class Api
    {
    public:
        explicit Api(const options& opt = MakeRequest::initOptionsFromConfig());

        MakeRequest Request() const
        {
            return *_request.get();
        };

    private:
        std::unique_ptr<MakeRequest> _request;
        std::shared_ptr<UserAccessToken> _userToken;

    };
}


#endif //TWITCHXX_API_H
