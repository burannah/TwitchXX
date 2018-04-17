//
// Created by buran on 17/04/18.
//

#ifndef TWITCHXX_WAITREQUEST_H
#define TWITCHXX_WAITREQUEST_H

#include <MakeRequest_Impl.h>
#include <map>

namespace TwitchXX
{
    class WaitRequest_Impl : public MakeRequest_Impl
    {
    public:
        web::json::value performRequest(const RequestParams &params) override;
    protected:
        const std::string test = "This is wait!";
    };
}


#endif //TWITCHXX_WAITREQUEST_H
