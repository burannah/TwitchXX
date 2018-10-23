//
// Created by buran on 29/01/18.
//

#include <Game.h>
#include <TwitchException.h>
#include <JsonWrapper.h>
#include "Api.h"

namespace TwitchXX
{
    namespace
    {
        web::uri getGetGamesUri(const std::vector<unsigned long long> &ids,
                                const std::vector<std::string> &names)
        {

            web::uri_builder builder("helix/games");
            addRangeOfParamsToBuilder(builder, "id", ids);
            addRangeOfParamsToBuilder(builder, "name", names);

            return builder.to_uri();
        }


        web::uri getTopGamesUri(int count, const char *cursor, const char *cursor_before)
        {
            web::uri_builder builder("helix/games/top");
            builder.append_query("first", count);

            if (cursor)
            {
                builder.append_query("after", cursor);
            }
            else if (cursor_before)
            {
                builder.append_query("before", cursor_before);
            }
            return builder.to_uri();
        }
    }

    Game::Game(const Api &api, unsigned long long int id, const std::string &name)
    {
        if(!id && name.empty())
        {
            throw TwitchException("Either name or id should be provided to get a game.");
        }

        auto response = api.reqWait().get(getGetGamesUri({id}, {name}));

        if(response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();
            JsonWrapper w(*data.begin());

            Id = w["id"];
            Name = w["name"].as_string();
            BoxArt = w["box_art_url"].as_string();
        }
    }

    Game::Game(unsigned long long id, const std::string &name, const std::string &url)
    : Id(id)
    , Name(name)
    , BoxArt(url)
    {
        if(!Id || Name.empty())
        {
            std::stringstream ss;
            ss << "Unable to create a game with Id:" << Id
               << " and Title:" << Name;
            throw TwitchException(ss.str().c_str());
        }
    }

    std::vector<Game>
    getGames(const Api &api, const std::vector<unsigned long long> &ids, const std::vector<std::string> &names)
    {
        if(ids.size() > 100 || names.size() > 100)
        {
            throw TwitchException("Too many games requested");
        }

        auto response = api.reqWait().get(getGetGamesUri(ids, names));
        std::vector<Game> result;

        if(response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& game: data)
            {
                JsonWrapper w(game);
                result.emplace_back(w["id"], w["name"].as_string(), w["box_art_url"].as_string());
            }
        }

        return result;
    }

    std::tuple<std::vector<Game>, std::string>
    getTopGames(const Api &api, int count, const char *cursor, const char *cursor_before)
    {
        if (count > 100)
        {
            throw TwitchException("getTopGames: count must be less or equal to 100");
        }

        auto response = api.reqWait().get(getTopGamesUri(count, cursor, cursor_before));
        std::vector<Game> result;

        if (response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& game: data)
            {
                JsonWrapper w(game);
                result.emplace_back(w["id"], w["name"], w["box_art_url"]);
            }
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
