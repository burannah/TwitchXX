//
// Created by buran on 03/03/18.
//

#include <StreamMetadata.h>
#include <JsonWrapper.h>
#include <iostream>

const std::string REMAINING_PARAM = "Ratelimit-Helixstreamsmetadata-Remaining";
const std::string LIMIT_PARAM = "Ratelimit-Helixstreamsmetadata-Limit";

namespace TwitchXX
{
    std::tuple<std::vector<TwitchXX::StreamMetadata>, std::string>
    getStreamsMetadata(const Api& api,
                       size_t count,
                       StreamMetadata::RateLimits* limits,
                       const char *cursor)
    {
        StreamsOptions opt;
        opt.first = count > 100 || count == 0 ? 20 : count;
        if(cursor)
        {
            opt.after = std::string(cursor);
        }

        opt.type = StreamType::Value::ALL;

        return getStreamsMetadata(api, opt, limits);
    }

    std::tuple<std::vector<StreamMetadata>, std::string>
    getStreamsMetadata(const Api& api,
                       const StreamsOptions &opt,
                       StreamMetadata::RateLimits* limits)
    {
        api.Request().setResponseHeaderParam(REMAINING_PARAM);
        api.Request().setResponseHeaderParam(LIMIT_PARAM);

        web::uri_builder builder("helix/streams/metadata");

        StreamsOptions::fillBuilder(builder,opt);

        auto response = api.Request().get(builder.to_uri());
        std::vector<StreamMetadata> result;
        if (response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            std::for_each(data.begin(), data.end(), [&](auto &&val)
            {
                JsonWrapper w(val);
                StreamMetadata s;
                s.UserId = *w["user_id"];
                s.GameId = *w["game_id"];

                if(val.has_field("overwatch") && !val.at("overwatch").is_null())
                {
                    Overwatch o;
                    JsonWrapper ow(val.at("overwatch").at("broadcaster").at("hero"));

                    s.overwatch = std::make_unique<Overwatch>();

                    s.overwatch->Name = static_cast<std::string>(*ow["name"]);
                    s.overwatch->Role = static_cast<std::string>(*ow["role"]);
                    s.overwatch->Ability = static_cast<std::string>(*ow["ability"]);
                }
                else if(val.has_field("hearthstone") && !val.at("hearthstone").is_null())
                {
                    Hearthstone h;
                    JsonWrapper broadcaster(val.at("hearthstone").at("broadcaster").at("hero"));
                    s.hearthstone = std::make_unique<Hearthstone>();

                    s.hearthstone->Broadcaster.Name = static_cast<std::string>(*broadcaster["name"]);
                    s.hearthstone->Broadcaster.Class = static_cast<std::string>(*broadcaster["class"]);
                    s.hearthstone->Broadcaster.Type = static_cast<std::string>(*broadcaster["type"]);

                    JsonWrapper opponent(val.at("hearthstone").at("opponent").at("hero"));

                    s.hearthstone->Opponent.Class = static_cast<std::string>(*opponent["class"]);
                    s.hearthstone->Opponent.Name = static_cast<std::string>(*opponent["name"]);
                    s.hearthstone->Opponent.Type = static_cast<std::string>(*opponent["type"]);
                }

                result.push_back(s);
            });
        }

        std::string new_cursor;
        try
        {
            new_cursor = response.at("pagination").at("cursor").as_string();
        }
        catch(web::json::json_exception& e)
        {
            new_cursor = "Error cursor!";
        }

        if(limits)
        {
            auto headers = api.Request().getResponseHeaderParams();
            limits->Remaining = std::atoi(headers[REMAINING_PARAM].c_str());
            limits->Limit = std::atoi(headers[LIMIT_PARAM].c_str());
        }

        return std::make_tuple(result, new_cursor);
    }

}
