//
// Created by buran on 17/01/18.
//

#include "Clip.h"
#include "MakeRequest.h"

TwitchXX::Clip::Handle TwitchXX::Clip::CreateAndGetHandle(const utility::string_t &broadcaster)
{
    TwitchXX::Clip::Handle handle;
    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder(U("/clips"));
    builder.append_query(U("broadcaster_id"),broadcaster);

    //TODO: Extract headers from the response
    auto response = request.post(builder.to_uri());
    if(response.has_field(U("data")) && !response.at(U("data")).is_null() && response.at(U("data")).size())
    {
        auto data = response.at(U("data")).as_array();

        handle.Id = data.begin()->at(U("id")).as_string();
        handle.EditUrl = data.begin()->at(U("edit_url")).as_string();
    }

    return handle;
}

TwitchXX::Clip::Clip(const utility::string_t &id)
{
    //TODO: send a request to get existing clip;
}
