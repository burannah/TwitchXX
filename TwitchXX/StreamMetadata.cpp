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
    namespace
    {
        Overwatch createOverwatch(const web::json::value &metadata)
        {
            Overwatch o;
            JsonWrapper ow(metadata.at("overwatch").at("broadcaster").at("hero"));

            o.Name = ow["name"].as_string();
            o.Role = ow["role"].as_string();
            o.Ability = ow["ability"].as_string();
            return o;
        }

        Hearthstone createHearthstone(const web::json::value &metadata)
        {
            Hearthstone h;
            JsonWrapper broadcaster(metadata.at("hearthstone").at("broadcaster").at("hero"));

            h.Broadcaster.Name = broadcaster["name"].as_string();
            h.Broadcaster.Class = broadcaster["class"].as_string();
            h.Broadcaster.Type = broadcaster["type"].as_string();

            JsonWrapper opponent(metadata.at("hearthstone").at("opponent").at("hero"));

            h.Opponent.Class = opponent["class"].as_string();
            h.Opponent.Name = opponent["name"].as_string();
            h.Opponent.Type = opponent["type"].as_string();
            return h;
        }

        StreamMetadata createMetadata(const web::json::value &metadata)
        {
            JsonWrapper w(metadata);
            StreamMetadata s;
            s.UserId = w["user_id"];
            s.GameId = w["game_id"];

            if(metadata.has_object_field("overwatch"))
            {
                s.overwatch = createOverwatch(metadata);

            }
            else if(metadata.has_object_field("hearthstone"))
            {
                s.hearthstone = createHearthstone(metadata);

            }
            return s;
        }
    }
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

        auto request = api.reqWait();
        request.setResponseHeaderParam(REMAINING_PARAM);
        request.setResponseHeaderParam(LIMIT_PARAM);

        web::uri_builder builder("helix/streams/metadata");

        StreamsOptions::fillBuilder(builder,opt);

        auto response = request.get(builder.to_uri());
        std::vector<StreamMetadata> result;
        if (response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& metadata: data)
            {
                result.push_back(createMetadata(metadata));
            }
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
            const auto& headers = request.getResponseHeaderParams();
            limits->Remaining = std::atoi(headers.at(REMAINING_PARAM).c_str());
            limits->Limit = std::atoi(headers.at(LIMIT_PARAM).c_str());
        }

        return std::make_tuple(result, new_cursor);
    }

}
