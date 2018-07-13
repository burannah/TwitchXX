//
// Created by buran on 13/07/18.
//

#ifndef TWITCHXX_TEAM_H
#define TWITCHXX_TEAM_H

#include <string>
#include <TwitchDef.h>

namespace TwitchXX
{
    namespace v5
    {
        class Team
        {
        public:
            unsigned long long Id;
            std::string        Background;
            std::string        Banner;
            Date               Created;
            std::string        DisplayName;
            std::string        Info;
            std::string        Logo;
            std::string        Name;
            Date               Updated;
        };
    }
}


#endif //TWITCHXX_TEAM_H
