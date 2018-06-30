#pragma once

#include <string>
#include <iostream>
#include <utility>
#include <memory>

#include <cpprest/http_msg.h>
#include <cpprest/http_client.h>


#include <TwitchDef.h>
#include <Request.h>
#include <Auth/AuthToken.h>

//#include <MakeRequest_Impl.h>

namespace web
{
    class uri;
}

namespace TwitchXX
{
    class MakeRequest_Impl;
    class UserAccessToken;

    ///Class to perform a web request.
    class RequestOnce : public Request
    {
    public:
        /// Constructor
        RequestOnce(const std::shared_ptr<MakeRequest_Impl>& impl,
                    const std::shared_ptr<AuthToken>& token)
        :Request(impl, token)
        {}

    protected:
        web::json::value performRequest(const RequestParams &params) override;
    };

}

