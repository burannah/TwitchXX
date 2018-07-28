//
// Created by buran on 03/07/18.
//
#include "Action.h"
#include <Api.h>
#include <JsonWrapper.h>

namespace TwitchXX
{
    namespace v5
    {
        std::vector<Action> getBits(const Api &api, const std::string &channelId)
        {
            web::uri_builder builder("kraken/bits/actions");
            if(!channelId.empty())
            {
                builder.append_query("channel_id", channelId);
            }
            std::vector<Action> result;

            auto response = api.reqWait().get(builder.to_uri());
            if(response.has_field("actions") && response.at("actions").is_array())
            {
                auto actions = response.at("actions").as_array();
                for(const auto& action: actions)
                {
                    JsonWrapper w(action);
                    Action a;
                    a.Backgrounds = w["backgrounds"].as_vector();
                    a.Prefix = w["prefix"].as_string();
                    a.Scales = w["scales"].as_vector();
                    a.States = w["states"].as_vector();

                    if(action.has_field("tiers") && action.at("tiers").is_array())
                    {
                        auto tiers = action.at("tiers").as_array();
                        for(const auto& tier: tiers)
                        {
                            Action::Tier t;
                            JsonWrapper ww(tier);
                            t.Colour = ww["color"].as_string();
                            t.Id = ww["id"];
                            auto images = tier.at("images");
                            Action::Tier::_BackgroundedImg b;

                            for(const auto& back: a.Backgrounds)
                            {
                                auto backgroundObj = images.at(back);

                                Action::Tier::_StatedImg st;

                                for(const auto& state: a.States)
                                {
                                    auto stateObj = backgroundObj.at(state);
                                    Action::Tier::_ScaledImg sc;

                                    for(const auto& scale: a.Scales)
                                    {
                                        auto scaleObj = stateObj.at(scale);

                                        sc.insert({scale, scaleObj.as_string()});
                                    }

                                    st.insert({state, sc});
                                }

                                b.insert({back, st});
                            }

                            t.Images = b;
                        }
                    }

                    result.push_back(std::move(a));
                }
            }

            return std::vector<TwitchXX::v5::Action>();
        }
    }
}
