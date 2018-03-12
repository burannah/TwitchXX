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
    class Api
    {
    public:
        explicit Api(const options& opt = MakeRequest::initOptionsFromConfig())
        :_request(std::make_shared<MakeRequest>(opt))
        {
        }

        std::shared_ptr<MakeRequest> Request() const
        {
            return _request;
        };

    private:
        std::shared_ptr<MakeRequest> _request;

    };
}


#endif //TWITCHXX_API_H
