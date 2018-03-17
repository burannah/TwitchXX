//
// Created by buran on 14/03/18.
//

#include <Video.h>
#include <VideoOptions.h>
#include <Api.h>
#include <TwitchException.h>
#include <JsonWrapper.h>
#include <Utility.h>

std::tuple<std::vector<TwitchXX::Video>, std::string>
TwitchXX::getVideos(const Api &api, const std::vector<uint64_t>& ids, uint64_t userId,
                    uint64_t gameId, const VideoOptions& opt)
{
    if(ids.size() > 100)
    {
        throw TwitchException("Too many video ids");
    }

    web::uri_builder builder("helix/videos");

    if(ids.size())
    {
        addRangeOfParamsToBuilder(builder, "id", ids);
    }
    else if(userId)
    {
        builder.append_query("user_id", userId);
    }
    else if(gameId)
    {
        builder.append_query("game_id", gameId);
    }
    else
    {
        throw TwitchException("Video id(s), user id or game id should be specified");
    }

    if(opt.After.size())
    {
        builder.append_query("after",opt.After);
    }
    else if(opt.Before.size())
    {
        builder.append_query("before", opt.Before);
    }


    builder.append_query("first", opt.Count > 100 || opt.Count < 1 ? 20 : opt.Count );

    if(opt.Language.size())
    {
        builder.append_query("language", opt.Language);
    }

    builder.append_query("period", VideoPeriodType::toString(opt.Period));

    builder.append_query("sort", VideoSortType::toString(opt.Sort));

    builder.append_query("type", VideoType::toString(opt.Type));

    auto response = api.Request()->get(builder.to_uri());
    std::vector<Video> result;


    if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();

        result.reserve(data.size());
        std::for_each(std::begin(data), std::end(data), [&](auto&& val)
        {
            result.emplace_back();
            auto& u = result.back();
            JsonWrapper w(val);

            u.Id = *w["id"];
            u.UserId = *w["user_id"];
            u.Title = static_cast<std::string>(*w["title"]);
            u.Description = static_cast<std::string>(*w["description"]);
            u.Created = DateFromString(*w["created_at"]);
            u.Published = DateFromString(*w["published_at"]);
            u.ThumbnailUrl = static_cast<std::string>(*w["thumbnail_url"]);
            u.ViewCount = *w["view_count"];
            u.Language = static_cast<std::string>(*w["language"]);
            u.Duration = static_cast<std::string>(*w["duration"]);
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



    return std::tuple<std::vector<TwitchXX::Video>, std::string>();
}
