//
// Created by buran on 04/02/18.
//

#ifndef TWITCHXX_USERACCESSTOKEN_H
#define TWITCHXX_USERACCESSTOKEN_H

#include <Auth/AuthToken.h>

namespace TwitchXX
{
    class UserAccessToken : public AuthToken
    {
    public:
        explicit UserAccessToken(const std::string& token = std::string());

        Date                    validTill() const override;
        std::string             get(AuthScope scope) override;
        std::shared_ptr<Handle> getHandle(AuthScope scope) override ;
        bool                    isValid() const override;
        std::string             tokenType() const override
        {
            return "UserAccessToken";
        }

    private:
        AuthScope   _scope{};
        std::string _token{};
    };
}



#endif //TWITCHXX_USERACCESSTOKEN_H
