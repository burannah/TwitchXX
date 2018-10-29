//
// Created by buran on 09/07/18.
//

#ifndef TWITCHXX_CHANNEL_H
#define TWITCHXX_CHANNEL_H

#include <string>

#include <TwitchDef.h>
#include <Api.h>
#include <BroadcasterType.h>
#include "User.h"
#include "Team.h"
#include "Subscription.h"

namespace TwitchXX
{
    class VideoOptions;

    namespace v5
    {
        class Video;

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
        Channel updateChannelStatus(const Api& api,
                                    const std::string& channelId,
                                    const std::string& status);
        Channel updateChannelDelay(const Api& api,
                                   const std::string& channelId,
                                   int delay);
        Channel updateChannelGame(const Api& api,
                                  const std::string& channelId,
                                  const std::string& game);
        Channel updateChannel(const Api& api,
                              const std::string& channelId,
                              const std::optional<std::string>& status,
                              const std::optional<std::string>& game,
                              const std::optional<int>& delay);

        std::vector<User> getChannelEditors(const Api& api, const std::string& channelId);

        std::vector<Team> getChannelTeams(const Api& api, const std::string& channelId);

        std::tuple<unsigned long long, std::vector<Subscription> >
        getChannelSubscriptions(const Api& api,
                                const std::string& channelId,
                                int limit = 100,
                                int offset = 0,
                                Direction::Value direction = Direction::Value::ASC);

        Subscription checkChannelSubscriptionByUser(const Api& api,
                                                    const std::string& channelId,
                                                    const std::string& userId);

        std::tuple<unsigned long long, std::vector<v5::Video>>
        getChannelVideos(const Api& api,
                         const std::string& channelId,
                         const VideoOptions* opt = nullptr);

    }
}



#endif //TWITCHXX_CHANNEL_H
