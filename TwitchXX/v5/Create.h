//
// Created by buran on 12/07/18.
//

#ifndef TWITCHXX_CREATE_H
#define TWITCHXX_CREATE_H

#include <cpprest/json.h>
#include <v5/User.h>

namespace TwitchXX
{
    namespace v5
    {
        User createUser(const web::json::value &rawUser);
    }
}

#endif //TWITCHXX_CREATE_H
