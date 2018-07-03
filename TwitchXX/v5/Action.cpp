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

            auto response = api.reqWait().post(builder.to_uri());
            if(response.has_field("actions") && !response.at("actions").is_null() && response.at("actions").is_array())
            {
                auto actions = response.at("actions").as_array();
                result.reserve(actions.size());
                std::for_each(std::begin(actions), std::end(actions),[&](const auto& action)
                {
                    JsonWrapper w(action);
                    Action a;
                    a.Backgrounds = w["backgrounds"]->as_vector();
                    a.Prefix = w["prefix"]->as_string();
                    a.Scales = w["scales"]->as_vector();
                    a.States = w["states"]->as_vector();

                    auto tiers = action.at("tiers").as_array();
                    std::for_each(std::begin(tiers), std::end(tiers),[&](const auto& tier)
                    {
                        Action::Tier t;
                        JsonWrapper ww(tier);
                        t.Colour = w["color"]->as_string();
                        t.Id = *w["id"];
                        auto images = tier.at("images");
                        Action::Tier::_BackgroundedImg b;
                        std::for_each(std::begin(a.Backgrounds), std::end(a.Backgrounds), [&](const std::string& back)
                        {
                            auto backgroundObj = images.at(back);

                            Action::Tier::_StatedImg st;
                            std::for_each(std::begin(a.States), std::end(a.States), [&](const std::string& state)
                            {
                                auto stateObj = backgroundObj.at(state);
                                Action::Tier::_ScaledImg sc;
                                std::for_each(std::begin(a.Scales), std::end(a.Scales), [&](const std::string& scale)
                                {
                                    auto scaleObj = stateObj.at(scale);

                                    sc.insert({scale, scaleObj.as_string()});
                                });
                                st.insert({state, sc});
                            });

                            b.insert({back, st});
                        });
                        t.Images = b;
                    });

                    result.push_back(std::move(a));
                });
            }

            return std::vector<TwitchXX::v5::Action>();
        }
    }
}
