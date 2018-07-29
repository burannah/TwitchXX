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
        std::vector<Subscription> getChannelSubscribers(const Api& api,
                                                        const std::string& channelId,
                                                        std::optional<int> limit,
                                                        Direction::Value dir)
        {
            web::uri_builder builder("kraken/channels/" + channelId + "/subscriptions");

            if(limit)
            {
                builder.append_query("limit", limit.value());
            }

            builder.append_query("direction", Direction::toString(dir));

            auto response = api.reqOnce().get(builder.to_uri(), AuthScope::CHANNEL_SUBSCRIPTIONS);

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
    }
}