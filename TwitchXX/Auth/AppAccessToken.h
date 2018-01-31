//
// Created by buran on 30/01/18.
//

#ifndef TWITCHXX_APPACCESSTOKEN_H
#define TWITCHXX_APPACCESSTOKEN_H

#include <Auth/AuthToken.h>
#include <memory>

namespace TwitchXX
{
    class AppAccessToken : public AuthToken
    {
        explicit AppAccessToken();

        Date validTill() const override
        {
            return _handle->_validTill;
        };
        bool isValid() const  override
        {
            return _handle->_validTill < std::chrono::system_clock::now();
        }

        std::string get() const override
        {
            if(!isValid())
            {
                refreshToken();
            }

            return _handle->_token;
        };

        std::shared_ptr<Handle> getHandle() const override
        {
            if(!isValid())
            {
                refreshToken();
            }

            return _handle;
        }

    private:
        std::shared_ptr<Handle> _handle;

        void refreshToken() const;
    };
}


#endif //TWITCHXX_APPACCESSTOKEN_H
