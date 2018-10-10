//
// Created by buran on 7/28/18.
//

#ifndef TWITCHXX_SUBSCRIPTION_H
#define TWITCHXX_SUBSCRIPTION_H

#include <string>
#include <Direction.h>
#include <TwitchDef.h>
#include <v5/User.h>

namespace TwitchXX
{
    class Api;

    namespace v5
    {
        class Subscription
        {
        public:
            std::string Id;
            Date        Created;
            std::string SubPlan;
            std::string SubPlanName;
            v5::User    User;
        };

        std::vector<Subscription> getChannelSubscribers(const Api &api,
                                                        const std::string &channelId,
                                                        const std::optional<int> &limit = std::nullopt,
                                                        Direction::Value dir = Direction::Value::ASC);

        Subscription checkChannelSubscriptionByUser(const Api& api,
                                                    const std::string& channelId,
                                                    const std::string& userId);
    }
};


#endif //TWITCHXX_SUBSCRIPTION_H
