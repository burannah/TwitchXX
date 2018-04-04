//
// Created by buran on 12/03/18.
//

#include <Api.h>
#include <MakeRequest.h>
#include <Auth/UserAccessToken.h>

TwitchXX::Api::Api(const TwitchXX::options &opt)
        :_request(std::make_unique<MakeRequest>(opt))
        ,_userToken(std::make_shared<UserAccessToken>(opt.at("token")))
{
    _request->setAuthToken(static_cast<std::shared_ptr<AuthToken>>(_userToken));
}
