//
// Created by buran on 03/03/18.
//

#include <Property.h>
#include <StreamMetadata.h>
#include <MakeRequest.h>
#include <JsonWrapper.h>

const std::string REMAINING_PARAM = "Ratelimit-Helixstreamsmetadata-Remaining";
const std::string LIMIT_PARAM = "Ratelimit-Helixstreamsmetadata-Limit";

namespace TwitchXX
{
    std::tuple<std::vector<TwitchXX::StreamMetadata>, std::string>
    getStreamsMetadata(size_t count,
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

        return getStreamsMetadata(opt, limits);
    }

    std::tuple<std::vector<StreamMetadata>, std::string>
    getStreamsMetadata(const StreamsOptions &opt,
                       StreamMetadata::RateLimits* limits)
    {
        MakeRequest request(MakeRequest::getOptions());
        request.setResponseHeaderParam(REMAINING_PARAM);
        request.setResponseHeaderParam(LIMIT_PARAM);

        web::uri_builder builder("helix/streams/metadata");

        StreamsOptions::fillBuilder(builder,opt);

        auto response = request.get(builder.to_uri());
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

                    o.Name = *ow["name"];
                    o.Role = *ow["role"];
                    o.Ability = *ow["ability"];

                    s.overwatch = new Overwatch(o);
                }
                else if(val.has_field("hearthstone") && !val.at("hearthstone").is_null())
                {
                    Hearthstone h;
                    JsonWrapper broadcaster(val.at("hearthstone").at("broadcaster").at("hero"));

                    h.Broadcaster.Name = *broadcaster["name"];
                    h.Broadcaster.Class = *broadcaster["class"];
                    h.Broadcaster.Type = *broadcaster["type"];

                    JsonWrapper opponent(val.at("hearthstone").at("opponent").at("hero"));

                    h.Opponent.Class = *opponent["class"];
                    h.Opponent.Name = *opponent["name"];
                    h.Opponent.Type = *opponent["type"];

                    s.hearthstone = new Hearthstone(h);
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
            auto headers = request.getResponseHeaderParams();
            limits->Remaining = std::atoi(headers[REMAINING_PARAM].c_str());
            limits->Limit = std::atoi(headers[LIMIT_PARAM].c_str());
        }

        return std::make_tuple(result, new_cursor);
    }

}
