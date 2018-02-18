//
// Created by buran on 30/01/18.
//

#ifndef TWITCHXX_APPACCESSTOKEN_H
#define TWITCHXX_APPACCESSTOKEN_H

#include <Auth/AuthToken.h>
#include <memory>
#include <MakeRequest.h>

namespace TwitchXX
{
    ///App auth token class
    class AppAccessToken : public AuthToken
    {
    public:
        explicit AppAccessToken();

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
        std::string get(AuthScope scope = AuthScope()) const override
        {
            if(!isValid() || (scope != AuthScope::NO_SCOPE && !(scope & _handle->_scope)))
            {
                _handle->_scope |= scope;
                refreshToken();
            }

            return "Bearer " + _handle->_token;
        };

        ///Get all token information
        std::shared_ptr<Handle> getHandle(AuthScope scope = AuthScope()) const override
        {
            if(!isValid() ||(scope != AuthScope::NO_SCOPE && !(scope & _handle->_scope)))
            {
                _handle->_scope |= scope;
                refreshToken();
            }

            return _handle;
        }

    private:
        std::shared_ptr<Handle> _handle;
        MakeRequest             _request;

        void refreshToken() const;
        void revoke();
    };
}


#endif //TWITCHXX_APPACCESSTOKEN_H
