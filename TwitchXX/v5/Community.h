//
// Created by buran on 10/30/18.
//

#ifndef TWITCHXX_COMMUNITY_H
#define TWITCHXX_COMMUNITY_H

#include <string>

namespace TwitchXX
{
    namespace v5
    {
        struct Community
        {
            std::string Id;
            std::string OwnerId;
            std::string Name;
            std::string DisplayName;
            std::string AvatarUrl;
            std::string CoverUrl;
            std::string Description;
            std::string DescriptionHtml;
            std::string Rules;
            std::string RulesHtml;
            std::string Language;
            std::string Summary;
        };
    }
}



#endif //TWITCHXX_COMMUNITY_H
