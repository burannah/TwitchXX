//
// Created by buran on 12/07/18.
//

#ifndef TWITCHXX_CREATE_H
#define TWITCHXX_CREATE_H

namespace web
{
    namespace json
    {
        class value;
    }
}

namespace TwitchXX
{
    namespace v5
    {
        class Subscription;
        class User;

        User createUser(const web::json::value &rawUser);
        Subscription createSubscription(const web::json::value& rawSub);
    }
}

#endif //TWITCHXX_CREATE_H
