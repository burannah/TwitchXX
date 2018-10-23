//
// Created by buran on 14/03/18.
//

#include <Video.h>
#include <VideoOptions.h>
#include <Api.h>
#include <TwitchException.h>
#include <JsonWrapper.h>
#include <Utility.h>
#include "UtilsInternal.h"

namespace TwitchXX
{
    namespace
    {
        web::uri getVideosUri(const std::vector<uint64_t>& ids,
                              uint64_t userId,
                              uint64_t gameId,
                              const VideoOptions& opt)
        {
            if(ids.size() > 100)
            {
                throw TwitchException("Too many video ids");
            }

            web::uri_builder builder("helix/videos");

            if(!ids.empty())
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

            if(!opt.After.empty())
            {
                builder.append_query("after",opt.After);
            }
            else if(!opt.Before.empty())
            {
                builder.append_query("before", opt.Before);
            }


            builder.append_query("first", opt.Count > 100 || opt.Count < 1 ? 20 : opt.Count );

            if(!opt.Language.empty())
            {
                builder.append_query("language", opt.Language);
            }

            builder.append_query("period", PeriodType::toString(opt.Period));
            builder.append_query("sort", VideoSortType::toString(opt.Sort));
            builder.append_query("type", VideoType::toString(opt.Type));

            return builder.to_uri();
        }

        Video createVideo(const web::json::value& video)
        {
            Video u;
            JsonWrapper w(video);

            u.Id = w["id"];
            u.UserId = w["user_id"];
            u.Title = w["title"].as_string();
            u.Description = w["description"].as_string();
            u.Created = w["created_at"];
            u.Published = w["published_at"];
            u.ThumbnailUrl = w["thumbnail_url"].as_string();
            u.ViewCount = w["view_count"];
            u.Language = w["language"].as_string();
            u.Duration = w["duration"].as_string();

            return u;
        }
    }

    std::tuple<std::vector<Video>, std::string>
    getVideos(const Api &api, const std::vector<uint64_t>& ids, uint64_t userId,
              uint64_t gameId, const VideoOptions& opt)
    {

        auto response = api.reqWait().get(getVideosUri(ids, userId, gameId, opt));
        std::vector<Video> result;


        if(response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& video: data)
            {
                result.push_back(createVideo(video));
            }
        }

        return std::make_tuple(result, UtilsInternal::getCursor(response));
    }
}
