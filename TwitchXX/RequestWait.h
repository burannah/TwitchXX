//
// Created by buran on 17/04/18.
//

#ifndef TWITCHXX_WAITREQUEST_H
#define TWITCHXX_WAITREQUEST_H

#include <Request.h>
#include <map>
#include <cpprest/json.h>

namespace TwitchXX
{
    /// Request object which is aware of requests per minute threshold.
    /// Will wait for next window upon getting CODE=429 - TOO MANY REQUESTS
    class RequestWait : public Request
    {
    public:
        /// Constructor
        RequestWait(const std::shared_ptr<MakeRequest_Impl> &impl,
                    const std::shared_ptr<AuthToken> &token);

    protected:
        /// virtual function defined in Request::performRequest.
        /// This method will be invoked for all request types: GET, PUT, POST, DEL
        web::json::value performRequest(const RequestParams &params) override;
    };
}


#endif //TWITCHXX_WAITREQUEST_H
