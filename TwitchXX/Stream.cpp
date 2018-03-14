//
// Created by buran on 23/02/18.
//

#include <Stream.h>
#include <TwitchException.h>
#include <MakeRequest.h>
#include <JsonWrapper.h>
#include <StreamsOptions.h>
#include <StreamType.h>

std::tuple<std::vector<TwitchXX::Stream>, std::string>
TwitchXX::getStreams(size_t count, const char *cursor)
{
    StreamsOptions opt;
    opt.first = count > 100 || count == 0 ? 20 : count;
    if(cursor)
    {
        opt.after = std::string(cursor);
    }

    opt.type = StreamType::Value::ALL;

    return getStreams(opt);
}


std::tuple<std::vector<TwitchXX::Stream>, std::string> TwitchXX::getStreams(const StreamsOptions &opt)
{
    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("helix/streams");

    StreamsOptions::fillBuilder(builder,opt);

    auto response = request.get(builder.to_uri());
    std::vector<Stream> result;

    if (response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();

        result.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](auto &&val)
        {
            JsonWrapper w(val);
            Stream s;
            s.Id = *w["id"];
            s.UserId = *w["user_id"];
            s.GameId = *w["game_id"];

            //TODO: Support array fields in Property class
            if(val.has_field("community_ids")
               && !val.at("community_ids").is_null()
               && val.at("community_ids").size())
            {
                auto communities = val.at("community_ids").as_array();
                auto proxy = s.CommunityIds.Get(); //I'm too lazy to specify the type
                std::for_each(communities.begin(), communities.end(), [&](auto&& c)
                {
                    proxy.push_back(c.as_string());
                });
                s.CommunityIds = proxy;
            }

            s.Type = StreamType::fromString(*w["type"]);
            s.Title = *w["title"];
            s.Viewers = *w["viewer_count"];
            s.Started = DateFromString(*w["started_at"]);
            s.Language = *w["language"];
            s.Thumb = *w["thumbnail_url"];

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

    return std::make_tuple(result, new_cursor);
}
