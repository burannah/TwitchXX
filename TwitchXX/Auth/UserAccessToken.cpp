//
// Created by buran on 04/02/18.
//

#include <TwitchException.h>
#include <MakeRequest.h>
#include <Auth/UserAccessToken.h>

TwitchXX::Date TwitchXX::UserAccessToken::validTill() const
{
    return std::chrono::system_clock::now() + std::chrono::hours(24*7);
}

std::string TwitchXX::UserAccessToken::get(TwitchXX::AuthScope scope)
{
    if(scope != AuthScope::NO_SCOPE && !(scope & _scope))
    {
        throw TwitchXX::TwitchException("UserAccessToken has no such scope");
    }
    return "Bearer " + _token;
}

bool TwitchXX::UserAccessToken::isValid() const
{
    return true;
}

std::shared_ptr<TwitchXX::AuthToken::Handle> TwitchXX::UserAccessToken::getHandle(TwitchXX::AuthScope scope)
{
    if(scope != AuthScope::NO_SCOPE && !(scope & _scope))
    {
        throw TwitchXX::TwitchException("UserAccessToken has no such scope");
    }
    auto handle = std::make_shared<Handle>();
    handle -> _token = this->_token;
    handle -> _scope = this->_scope;
    handle->_validTill = this->validTill();
    handle->_refresh_token = "";
    return handle;
}

TwitchXX::UserAccessToken::UserAccessToken(const std::string &token)
{
    if(token.size())
    {
        _token = token;
    }
    else
    {
        _token = (MakeRequest::getOptions())["token"];
    }

    //TODO: Make it real parameter from config
    _scope = AuthScope::CLIPS_EDIT
            | AuthScope::USER_EDIT
            | AuthScope::USER_READ_EMAIL;
}
