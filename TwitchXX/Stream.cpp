//
// Created by buran on 23/02/18.
//

#include <Stream.h>
#include <TwitchException.h>
#include <JsonWrapper.h>
#include <StreamsOptions.h>
#include <StreamType.h>
#include <Utility.h>
#include <Api.h>
#include "UtilsInternal.h"

namespace TwitchXX
{
    namespace
    {
        Stream createStream(const web::json::value& stream)
        {
            JsonWrapper w(stream);
            Stream s;
            s.Id = w["id"];
            s.UserId = w["user_id"];
            s.GameId = w["game_id"];

            if(stream.has_array_field("community_ids"))
            {
                for(const auto& community: stream.at("community_ids").as_array())
                {
                    s.CommunityIds.push_back(community.as_string());
                }
            }

            s.Type = StreamType::fromString(w["type"].as_string());
            s.Title = w["title"].as_string();
            s.Viewers = w["viewer_count"];
            s.Started = w["started_at"];
            s.Language = w["language"].as_string();
            s.Thumb = w["thumbnail_url"].as_string();

            return s;
        }
    }

    std::tuple<std::vector<Stream>, std::string>
    getStreams(const Api &api, size_t count, const char *cursor)
    {
        StreamsOptions opt;
        opt.first = count > 100 || count == 0 ? 20 : count;
        if(cursor)
        {
            opt.after = std::string(cursor);
        }

        opt.type = StreamType::Value::ALL;

        return getStreams(api, opt);
    }


    std::tuple<std::vector<Stream>, std::string>
    getStreams(const Api &api, const StreamsOptions &opt)
    {
        web::uri_builder builder("helix/streams");

        StreamsOptions::fillBuilder(builder,opt);

        auto response = api.reqWait().get(builder.to_uri());
        std::vector<Stream> result;

        if (response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& stream: data)
            {
                result.push_back(createStream(stream));
            }
        }

        return std::make_tuple(result, UtilsInternal::getCursor(response));
    }
}
