//
// Created by buran on 7/28/18.
//

#ifndef TWITCHXX_SUBSCRIPTION_H
#define TWITCHXX_SUBSCRIPTION_H

namespace TwitchXX
{
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

        std::vector<Subscription> getChannelSubscribers(const Api& api,
                                                        const std::string& channelId,
                                                        int limit = 25,
                                                        Direction dir = Direction::Value::ASC);
    }
};


#endif //TWITCHXX_SUBSCRIPTION_H
