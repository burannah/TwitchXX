//
// Created by buran on 17/01/18.
//

#include "Clip.h"
#include "MakeRequest.h"

TwitchXX::Clip::Handle TwitchXX::Clip::CreateAndGetHandle(const utility::string_t &broadcaster)
{
    TwitchXX::Clip::Handle handle;
    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("/clips");
    builder.append_query("broadcaster_id",broadcaster);

    //TODO: Extract headers from the response
    auto response = request.post(builder.to_uri());
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
    //TODO: send a request to get existing clip;
}
