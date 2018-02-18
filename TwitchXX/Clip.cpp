//
// Created by buran on 17/01/18.
//

#include <Auth/UserAccessToken.h>
#include "Clip.h"
#include "MakeRequest.h"
#include "JsonWrapper.h"

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

        Id.Set(*w["id"]);
        Url.Set(*w["url"]);
        EmbedUrl.Set(*w["embed_url"]);
        BroadcasterId.Set(*w["broadcaster_id"]);
        CreatorId.Set(*w["creator_id"]);
        VideoId.Set(*w["video_id"]);
        GameId.Set(*w["game_id"]);
        Language.Set(*w["language"]);
        Title.Set(*w["title"]);
        ViewCount.Set(*w["view_count"]);
        Created.from_string(*w["created_at"]);
        Thumb.Set(*w["thumbnail_url"]);
    }
}
