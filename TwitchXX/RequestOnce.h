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

    ///Class to perform a web request.
    class RequestOnce : public Request
    {
    public:
		///MakerRequest constructor
		explicit RequestOnce(const std::map<utility::string_t, utility::string_t> &options,
                             const std::shared_ptr<MakeRequest_Impl> &rImpl)
        :Request(options, rImpl)
        {}

    protected:
        virtual web::json::value performRequest(const RequestParams &params) const override;
    };

}

