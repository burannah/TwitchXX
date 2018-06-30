//
// Created by buran on 12/03/18.
//

#include <Api.h>
#include <Auth/UserAccessToken.h>
#include <MakeRequest_Impl.h>

namespace TwitchXX
{
    Api::Api(const TwitchXX::options &opt)
    :_requestImpl(std::make_shared<MakeRequest_Impl>(opt))
    ,_userToken(std::make_shared<UserAccessToken>(opt.at("token")))
    ,_requestOnce(_requestImpl, _userToken)
    , _requestWait(_requestImpl, _userToken)
    ,_api_key(opt.at("api_key"))
    ,_client_secret(opt.at("client_secret"))
    {
    }
}
