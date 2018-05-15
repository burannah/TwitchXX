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
    class RequestWait : public Request
    {
    public:
        RequestWait(const std::map<utility::string_t, utility::string_t> &options,
                    const std::shared_ptr<MakeRequest_Impl> &impl);

    protected:
        web::json::value performRequest(const RequestParams &params) override;
    };
}


#endif //TWITCHXX_WAITREQUEST_H
