//
// Created by buran on 7/28/18.
//

#include "Subscription.h"

#include <JsonWrapper.h>
#include <v5/Create.h>
#include <TwitchException.h>
#include <Api.h>


namespace TwitchXX
{
    namespace v5
    {
        namespace
        {
            web::uri_builder createGetChannelSubscribersBuilder(const std::string& channelId,
                                                                const std::optional<int>& limit,
                                                                Direction::Value dir)
            {
                web::uri_builder builder("kraken/channels/" + channelId + "/subscriptions");

                if(limit)
                {
                    builder.append_query("limit", limit.value());
                }

                builder.append_query("direction", Direction::toString(dir));

                return builder;
            }
        }
        
        Subscription createSubscription(const web::json::value& rawSub)
        {
            if(rawSub.is_null())
            {
                throw TwitchException("Invalid subscription object");
            }

            JsonWrapper w(rawSub);

            Subscription s;

            s.Created = w["created_at"];
            s.Id = w["_id"].as_string();
            s.SubPlan = w["sub_plan"].as_string();
            s.SubPlanName = w["sub_plan_name"].as_string();
            s.User = createUser(rawSub.at("user"));

            return s;
        }
        std::vector<Subscription> getChannelSubscribers(const Api &api,
                                                        const std::string &channelId,
                                                        const std::optional<int> &limit,
                                                        Direction::Value dir)
        {
            auto response = api.reqOnce().get(createGetChannelSubscribersBuilder(channelId, limit,  dir).to_uri(),
                                              AuthScope::CHANNEL_SUBSCRIPTIONS);

            std::vector<Subscription> result;

            if(response.has_field("subscription") && response.at("subscription").is_array())
            {
                for(auto&& rawSub: response.at("subscription").as_array())
                {
                    result.push_back(createSubscription(rawSub));
                }
            }

            return result;
        }

        Subscription checkChannelSubscriptionByUser(const Api& api,
                                                    const std::string& channelId,
                                                    const std::string& userId)
        {
            web::uri_builder builder("kraken/channels/" + channelId + "/subscriptions/" + userId);

            auto response = api.reqOnce().get(builder.to_uri(), AuthScope::CHANNEL_CHECK_SUBSCRIPTION);

            Subscription result{};

            if(!response.is_null() && response.has_field("user"))
            {
                result = createSubscription(response);
            }

            return result;

        }
    }
}