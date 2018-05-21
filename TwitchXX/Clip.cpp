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

TwitchXX::Clip::Handle TwitchXX::Clip::CreateAndGetHandle(const Api &api, unsigned long long int broadcaster)
{
    TwitchXX::Clip::Handle handle;
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

TwitchXX::Clip::Clip(const Api &api, const std::string &id)
{
    web::uri_builder builder("helix/clips");
    builder.append_query("id",id);

    auto response = api.reqWait().get(builder.to_uri());

    if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();
        const auto& clip = *data.begin();
        JsonWrapper w(clip);

        Id = static_cast<std::string>(*w["id"]);
        Url = static_cast<std::string>(*w["url"]);
        EmbedUrl = static_cast<std::string>(*w["embed_url"]);
        BroadcasterId = *w["broadcaster_id"];
        CreatorId = *w["creator_id"];
        VideoId = *w["video_id"];
        GameId = *w["game_id"];
        Language = static_cast<std::string>(*w["language"]);
        Title = static_cast<std::string>(*w["title"]);
        ViewCount = *w["view_count"];
        Created = DateFromString(*w["created_at"]);
        Thumb = static_cast<std::string>(*w["thumbnail_url"]);
    }
}

bool TwitchXX::Clip::operator==(const TwitchXX::Clip &other) const
{
    return Id == other.Id;
}


std::tuple<std::vector<TwitchXX::Clip>, std::string>
TwitchXX::getClips(const Api &api, const ClipOptions& params)
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


    auto response = api.reqWait().get(builder.to_uri());
    std::vector<Clip> result;

    if (response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();

        result.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](auto &&val)
        {
            JsonWrapper w(val);

            result.emplace_back();
            Clip& clip = result.back();

            clip.Id = static_cast<std::string>(*w["id"]);
            clip.Url = static_cast<std::string>(*w["url"]);
            clip.EmbedUrl = static_cast<std::string>(*w["embed_url"]);
            clip.BroadcasterId = *w["broadcaster_id"];
            clip.CreatorId = *w["creator_id"];
            clip.VideoId = *w["video_id"];
            clip.GameId = *w["game_id"];
            clip.Language = static_cast<std::string>(*w["language"]);
            clip.Title = static_cast<std::string>(*w["title"]);
            clip.ViewCount = *w["view_count"];
            clip.Created = DateFromString(*w["created_at"]);
            clip.Thumb = static_cast<std::string>(*w["thumbnail_url"]);


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
