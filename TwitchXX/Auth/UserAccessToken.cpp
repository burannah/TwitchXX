//
// Created by buran on 04/02/18.
//

#include <RequestOnce.h>
#include <TwitchException.h>
#include <Auth/UserAccessToken.h>
#include <Log.h>

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

    if(scope == AuthScope::CHANNEL_READ || scope == AuthScope::CHANNEL_EDITOR)
    {
        return "OAuth " + _token;
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
:_token(token)
{
    if(token.empty())
    {
        const std::string error = "User access token can not be empty";
        Log::Warn(error);
        throw TwitchException(error.c_str());
    }

    //TODO: Make it real parameter from config
    _scope = AuthScope::CLIPS_EDIT
            | AuthScope::USER_EDIT
            | AuthScope::USER_READ_EMAIL
            | AuthScope::BITS_READ
            | AuthScope::CHANNEL_READ
            | AuthScope::CHANNEL_EDITOR
            | AuthScope::CHANNEL_SUBSCRIPTIONS;
}
