//
// Created by buran on 29/01/18.
//

#include <Game.h>
#include <TwitchException.h>
#include <MakeRequest.h>
#include <JsonWrapper.h>

TwitchXX::Game::Game(const std::string &id, const std::string &name)

{
    if(id.empty() && name.empty())
    {
        throw TwitchException("Either name or id should be provided to get a game.");
    }

    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("helix/games");
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

std::vector<TwitchXX::Game> TwitchXX::getGames(const std::vector<std::string>& ids,
                                               const std::vector<std::string>& names)
{
    if(ids.size() > 100 || names.size() > 100)
    {
        throw TwitchXX::TwitchException("Too many games requested");
    }

    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("helix/games");
    std::for_each(std::begin(ids), std::end(ids), [&](const auto& id)
    {
        builder.append_query("id", id);
    });
    std::for_each(std::begin(names), std::end(names), [&](const auto& name)
    {
        builder.append_query("name", name);
    });

    auto response = request.get(builder.to_uri());
    std::vector<Game> result;

    if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();

        result.reserve(data.size());
        std::for_each(data.begin(),data.end(),[&](auto&& val)
        {
            JsonWrapper w(val);
            result.emplace_back(*w["id"], *w["name"], *w["box_art_url"]);
        });
    }

    return result;
}


std::tuple<std::vector<TwitchXX::Game>, std::string> TwitchXX::getTopGames(int count, const char *cursor, const char *cursor_before)
{
    if (count > 100)
    {
        throw TwitchException("getTopGames: count must be less or equal to 100");
    }

    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("helix/games/top");
    builder.append_query("first", count);

    if (cursor)
    {
        builder.append_query("after", cursor);
    } else if (cursor_before)
    {
        builder.append_query("before", cursor_before);
    }

    auto response = request.get(builder.to_uri());
    std::vector<Game> result;

    if (response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();

        result.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](auto &&val)
        {
            JsonWrapper w(val);
            result.emplace_back(*w["id"], *w["name"], *w["box_art_url"]);
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
