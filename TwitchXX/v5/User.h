//
// Created by buran on 05/07/18.
//

#ifndef TWITCHXX_USER_H
#define TWITCHXX_USER_H

#include <string>
#include <TwitchDef.h>
#include <UserType.h>

namespace TwitchXX
{
    namespace v5
    {
        class User
        {
        public:
            unsigned long long Id;
            std::string Bio;
            Date        Created;
            std::string DisplayName;
            std::string Logo;
            std::string Name;
            UserType::Value Type;
            Date        Updated;
        };
    }
}

#endif //TWITCHXX_USER_H
