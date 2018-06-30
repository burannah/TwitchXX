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
    ,_requestOnce(opt, _requestImpl)
    ,_requestWait(opt, _requestImpl)
    ,_api_key(opt.at("api_key"))
    ,_client_secret(opt.at("client_secret"))
    {
        _requestOnce.setAuthToken(_userToken);
        _requestWait.setAuthToken(_userToken);
    }
}
