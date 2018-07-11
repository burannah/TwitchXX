//
// Created by buran on 09/07/18.
//

#ifndef TWITCHXX_CHANNEL_H
#define TWITCHXX_CHANNEL_H

#include <string>

#include <TwitchDef.h>
#include <Api.h>
#include <BroadcasterType.h>

namespace TwitchXX
{
    namespace v5
    {
        class Channel
        {
        public:
            bool    Mature;
            std::string Status;
            std::string BroadcasterLang;
            std::string DisplayName;
            std::string GameName;
            std::string Language;
            std::string Id;
            std::string Name;
            Date        Created;
            Date        Updated;
            bool        Partner;
            std::string Logo;
            std::string VideoBanner;
            std::string ProfileBanner;
            std::string ProfileBannerBkColor;
            std::string Url;
            unsigned long long Views;
            unsigned long long Followers;
            TwitchXX::BroadcasterType::Value BroadcasterType;
            std::string Key;
            std::string Email;
        };

        Channel getSelfChannel(const Api& api);
        Channel getChannel(const Api& api, const std::string& id);
    }
}



#endif //TWITCHXX_CHANNEL_H
