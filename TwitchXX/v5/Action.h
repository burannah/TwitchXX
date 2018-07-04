//
// Created by buran on 03/07/18.
//

#ifndef TWITCHXX_ACTION_H
#define TWITCHXX_ACTION_H

#include <vector>
#include <string>
#include <map>

namespace TwitchXX
{
    class Api;

    namespace v5
    {
        class Action
        {
        public:

            class Tier
            {
            public:
                typedef std::map<std::string, std::string> _ScaledImg;
                typedef std::map<std::string, _ScaledImg> _StatedImg;
                typedef std::map<std::string, _StatedImg> _BackgroundedImg;

                std::string        Colour;
                unsigned long long Id;
                _BackgroundedImg   Images;
            };
            std::vector<std::string> Backgrounds;
            std::string              Prefix;
            std::vector<std::string> Scales;
            std::vector<std::string> States;
            std::vector<Tier>        Tiers;
        };

        /// Fetch the cheermotes
        /// @param api - api object for request
        /// @param channelId - (optional) channel to retrieve cheermotes for
        /// @returns - vector of Action objects.
        std::vector<Action> getBits(const Api &api, const std::string &channelId = std::string());
    }
}



#endif //TWITCHXX_ACTION_H
