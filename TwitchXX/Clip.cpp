//
// Created by buran on 17/01/18.
//

#include <Auth/UserAccessToken.h>
#include <Clip.h>
#include <JsonWrapper.h>
#include <Utility.h>
#include <Api.h>
#include <ClipOptions.h>
#include <TwitchException.h>
#include <Log.h>
namespace TwitchXX
{
    namespace
    {
        web::uri_builder createGetClipsBuilder(const ClipOptions& params)
        {
            if (params.first > 100 || params.first < 1)
            {
                const std::string err = "getClips: count must be not greater then 100.";
                Log::Error(err);
                throw TwitchException(err.c_str());
            }

            web::uri_builder builder("helix/clips");
            if(!params.ids.empty())
            {
                addRangeOfParamsToBuilder(builder, "id", params.ids);
            }
            else if (params.broadcasterId)
            {
                builder.append_query("broadcaster_id", params.broadcasterId);
            }
            else if (params.gameId)
            {
                builder.append_query("game_id", params.gameId);
            }
            else
            {
                const std::string err = "For a query to be valid, id, broadcaster_id, or game_id must be specified.";
                Log::Error(err);
                throw TwitchException(err.c_str());
            }

            if(!params.after.empty())
            {
                builder.append_query("after", params.after);
            }
            else if(!params.before.empty())
            {
                builder.append_query("before", params.before);
            }

            builder.append_query("first", params.first);

            return builder;
        }

    }
    Clip::Handle Clip::CreateAndGetHandle(const Api &api, unsigned long long int broadcaster)
    {
        Clip::Handle handle;
        web::uri_builder builder("helix/clips");
        builder.append_query("broadcaster_id",broadcaster);

        auto response = api.reqWait().post(builder.to_uri(), AuthScope::CLIPS_EDIT);
        if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
        {
            auto data = response.at("data").as_array();

            handle.Id = data.begin()->at("id").as_string();
            handle.EditUrl = data.begin()->at("edit_url").as_string();
        }

        return handle;
    }

    Clip::Clip(const Api &api, const std::string &id)
    {
        web::uri_builder builder("helix/clips");
        builder.append_query("id",id);

        auto response = api.reqWait().get(builder.to_uri());

        if(response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();
            const auto& clip = *data.begin();
            JsonWrapper w(clip);

            Id = w["id"].as_string();
            Url = w["url"].as_string();
            EmbedUrl = w["embed_url"].as_string();
            BroadcasterId = w["broadcaster_id"];
            CreatorId = w["creator_id"];
            VideoId = w["video_id"];
            GameId = w["game_id"];
            Language = w["language"].as_string();
            Title = w["title"].as_string();
            ViewCount = w["view_count"];
            Created = w["created_at"];
            Thumb = w["thumbnail_url"].as_string();
        }
    }

    bool Clip::operator==(const Clip &other) const
    {
        return Id == other.Id;
    }


    Clip createClip(const web::json::value &clip)
    {
        JsonWrapper w(clip);

        Clip result;

        result.Id = w["id"].as_string();
        result.Url = w["url"].as_string();
        result.EmbedUrl = w["embed_url"].as_string();
        result.BroadcasterId = w["broadcaster_id"];
        result.CreatorId = w["creator_id"];
        result.VideoId = w["video_id"];
        result.GameId = w["game_id"];
        result.Language = w["language"].as_string();
        result.Title = w["title"].as_string();
        result.ViewCount = w["view_count"];
        result.Created = w["created_at"];
        result.Thumb = w["thumbnail_url"].as_string();

        return result;
    }

    std::tuple<std::vector<Clip>, std::string>
    getClips(const Api &api, const ClipOptions& params)
    {
        auto response = api.reqWait().get(createGetClipsBuilder(params).to_uri());
        std::vector<Clip> result;

        if (response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& clip: data)
            {
                result.push_back(createClip(clip));
            };
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
}
