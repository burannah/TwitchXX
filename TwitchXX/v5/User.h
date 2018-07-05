//
// Created by buran on 05/07/18.
//

#ifndef TWITCHXX_USER_H
#define TWITCHXX_USER_H

#include <string>
#include <TwitchDef.h>

namespace TwitchXX
{
    namespace v5
    {
        class User
        {
        public:
            std::string Id;
            std::string Bio;
            Date        Created;
            std::string DisplayName;
            std::string Logo;
            std::string Name;
            std::string Type;
            Date        Updated;
        };
    }
}

#endif //TWITCHXX_USER_H
