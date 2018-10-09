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
        namespace
        {
            void makeGetBitsParams(web::uri_builder& builder, const std::string& channelId)
            {
                if(!channelId.empty())
                {
                    builder.append_query("channel_id", channelId);
                }
            }

            Action::Tier makeTier(const web::json::value& tier, const Action& a)
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

                return t;
            }

            Action makeAction(const web::json::value& action)
            {
                JsonWrapper w(action);
                Action a;
                a.Backgrounds = w["backgrounds"].as_vector();
                a.Prefix = w["prefix"].as_string();
                a.Scales = w["scales"].as_vector();
                a.States = w["states"].as_vector();

                if(action.has_array_field("tiers"))
                {
                    auto tiers = action.at("tiers").as_array();
                    for(const auto& tier: tiers)
                    {
                        a.Tiers.push_back(makeTier(tier, a));
                    }
                }

                return a;

            }

            std::vector<Action> getBitsVector(web::json::value response)
            {
                std::vector<Action> result;
                if(response.has_array_field("actions"))
                {
                    auto actions = response.at("actions").as_array();
                    for(const auto& action: actions)
                    {
                        result.push_back(makeAction(action));
                    }
                }

                return result;
            }
        }

        std::vector<Action> getBits(const Api &api, const std::string &channelId)
        {
            web::uri_builder builder("kraken/bits/actions");

            makeGetBitsParams(builder, channelId);

            return getBitsVector(api.reqWait().get(builder.to_uri()));
        }
    }
}
