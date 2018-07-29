//
// Created by buran on 30/01/18.
//

#ifndef TWITCHXX_AUTHTOKEN_H
#define TWITCHXX_AUTHTOKEN_H

#include <string>
#include <chrono>
#include <memory>

#include<TwitchDef.h>

namespace TwitchXX
{
    ///Authorization scopes
    enum class AuthScope : unsigned
    {
        NO_SCOPE = 0,
        CLIPS_EDIT = 1 << 0,
        USER_EDIT = 1 << 1,
        USER_READ_EMAIL = 1 << 2,
        BITS_READ = 1 << 3,
        CHANNEL_READ = 1 << 4,
        CHANNEL_EDITOR = 1 << 5,
        CHANNEL_SUBSCRIPTIONS = 1 << 6
        /*
        USER_READ = 1 << 0,
        USER_BLOCKS_EDIT = 1 << 1,
        USER_BLOCKS_READ = 1 << 2,
        USER_FOLLOWS_EDIT = 1 << 3,
,

        CHANNEL_COMMERCIAL = 1 << 6,
        CHANNEL_STREAM = 1 << 7,
        ,
        USER_SUBSCRIPTIONS = 1 << 9,
        CHANNEL_CHECK_SUBSCRIPTION = 1 << 10,
        CHAT_LOGIN = 1 << 11,
        CHANNEL_FEED_READ = 1 << 12,
        CHANNEL_FEED_EDIT = 1 << 13 */
    };
    //@{
    /** Manipulations with AuthScope */
    using T = std::underlying_type_t<AuthScope>;
    inline AuthScope operator|(AuthScope lhs, AuthScope rhs)
    {
        return static_cast<AuthScope>((static_cast<T>(lhs)) | (static_cast<T>(rhs)));
    }

    inline AuthScope operator|=(AuthScope lhs, AuthScope rhs)
    {
        lhs = static_cast<AuthScope>(static_cast<T>(lhs) | static_cast<T>(rhs));
        return lhs;
    }

    inline bool operator&(AuthScope lhs, AuthScope rhs)
    {
        return (static_cast<T>(lhs) & static_cast<T>(rhs)) != 0;
    }
    //@}

    ///General base class for auth tokens
    class AuthToken
    {
    public:
        ///Auxiliary class that contains token data
        struct Handle
        {
            AuthScope   _scope{};
            Date        _validTill{};
            std::string _token{};
            std::string _refresh_token{};
        };


        virtual Date                    validTill() const = 0;
        virtual std::string             get(AuthScope scope = AuthScope()) = 0;
        virtual std::shared_ptr<Handle> getHandle(AuthScope scope = AuthScope()) = 0;
        virtual bool                    isValid() const = 0;
        virtual std::string             tokenType() const = 0;
    };
}

#endif //TWITCHXX_AUTHTOKEN_H
