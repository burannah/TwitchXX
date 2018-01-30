//
// Created by buran on 29/01/18.
//

#include "Game.h"
#include "TwitchException.h"
#include "MakeRequest.h"
#include "JsonWrapper.h"

TwitchXX::Game::Game(const std::string &id, const std::string &name)

{
    if(id.empty() && name.empty())
    {
        throw TwitchException("Either name or id should be provided to get a game.");
    }

    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("games");
    if(!id.empty())
    {
        builder.append_query("id",id);
    }
    if(!name.empty())
    {
        builder.append_query("name",name);
    }

    auto response = request.get(builder.to_uri());

    if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();
        JsonWrapper w(*data.begin());

        Id = *w["id"];
        Name = *w["name"];
        BoxArt = *w["box_art_url"];
    }
}

TwitchXX::Game::Game(const std::string &id, const std::string &name, const std::string &url)
: Id(id)
, Name(name)
, BoxArt(url)
{
    if(Id.Get().empty() || Id.Get().empty())
    {
        std::stringstream ss;
        ss << "Unable to create a game with Id:" << Id.Get()
           << " and Title:" << Name.Get();
        throw TwitchException(ss.str().c_str());
    }
}
