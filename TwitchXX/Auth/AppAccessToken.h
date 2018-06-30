//
// Created by buran on 30/01/18.
//

#ifndef TWITCHXX_APPACCESSTOKEN_H
#define TWITCHXX_APPACCESSTOKEN_H

#include <Auth/AuthToken.h>
#include <memory>
#include <RequestOnce.h>

namespace TwitchXX
{
    class MakeRequest_Impl;

    ///App auth token class
    class AppAccessToken : public AuthToken
    {
    public:
        explicit AppAccessToken(const std::string &apiKey, const std::string &clientSecret);

        ~AppAccessToken()
        {
            revoke();
        }

        ///Get date until this token is valid
        Date validTill() const override
        {
            return _handle->_validTill;
        };

        ///Does this token is valid?
        bool isValid() const  override
        {
            return _handle && _handle->_validTill > std::chrono::system_clock::now();
        }

        ///Get the token's auth string
        std::string get(AuthScope scope = AuthScope()) override
        {
            if(!isValid() || (scope != AuthScope::NO_SCOPE && !(scope & _handle->_scope)))
            {
                _handle->_scope |= scope;
                refreshToken();
            }

            return "Bearer " + _handle->_token;
        };

        ///Get all token information
        std::shared_ptr<Handle> getHandle(AuthScope scope = AuthScope()) override
        {
            if(!isValid() ||(scope != AuthScope::NO_SCOPE && !(scope & _handle->_scope)))
            {
                _handle->_scope |= scope;
                refreshToken();
            }

            return _handle;
        }

        ///Return token type as string
        std::string tokenType() const override
        {
            return "AppAccessToken";
        }
    private:
        std::shared_ptr<Handle>           _handle;
        options                           _opt;
        std::shared_ptr<MakeRequest_Impl> _request_impl;

        void refreshToken();
        void revoke();
    };
}


#endif //TWITCHXX_APPACCESSTOKEN_H
