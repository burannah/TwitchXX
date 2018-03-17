//
// Created by buran on 17/01/18.
//

#include <Auth/UserAccessToken.h>
#include <Clip.h>
#include <MakeRequest.h>
#include <JsonWrapper.h>
#include <Utility.h>

TwitchXX::Clip::Handle TwitchXX::Clip::CreateAndGetHandle(const utility::string_t &broadcaster)
{
    TwitchXX::Clip::Handle handle;
    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("/clips");
    builder.append_query("broadcaster_id",broadcaster);
    request.setAuthToken(std::make_shared<UserAccessToken>());

    //TODO: Extract headers from the response
    auto response = request.post(builder.to_uri(), AuthScope::CLIPS_EDIT);
    if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();

        handle.Id = data.begin()->at("id").as_string();
        handle.EditUrl = data.begin()->at("edit_url").as_string();
    }

    return handle;
}

TwitchXX::Clip::Clip(const utility::string_t &id)
{
    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("helix/clips");
    builder.append_query("id",id);

    auto response = request.get(builder.to_uri());

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
