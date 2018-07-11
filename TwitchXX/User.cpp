//
// Created by buran on 05/03/18.
//

#include <User.h>
#include <Auth/UserAccessToken.h>
#include <TwitchException.h>
#include <Api.h>
#include <JsonWrapper.h>

namespace TwitchXX
{
    User getUser(const Api &api, std::string id, std::string login)
    {
        if(!id.empty())
        {
            return getUsers(api, {id}, {})[0];
        }
        else if(!login.empty())
        {
            return getUsers(api, {}, {login})[0];
        }
        else
        {
            throw TwitchXX::TwitchException("Either login or user id should be specified!");
        }
    }

    std::vector<User> getUsers(const Api &api, std::vector<std::string> ids, std::vector<std::string> logins)
    {
        if(ids.empty() && logins.empty())
        {
            throw TwitchXX::TwitchException("Either login or user id should be specified!");
        }

        web::uri_builder builder("helix/users");

        addRangeOfParamsToBuilder(builder, "id", ids);
        addRangeOfParamsToBuilder(builder, "login", logins);

        auto response = api.reqWait().get(builder.to_uri());

        std::vector<User> result;

        if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());

            std::for_each(std::begin(data), std::end(data), [&](const auto &val)
            {
                JsonWrapper w(val);
                result.emplace_back();
                auto& u = result.back();
                u.Id = w["id"].as_string();
                u.Login = w["login"].as_string();
                u.DisplayName = w["display_name"].as_string();
                u.Type = UserType::fromString(w["type"].as_string());
                u.BroadcaterType = BroadcasterType::fromString(w["broadcaster_type"].as_string());
                u.Description = w["description"].as_string();
                u.AvatarUrl = w["profile_image_url"].as_string();
                u.OfflineImageUrl = w["offline_image_url"].as_string();
                u.ViewCount = w["view_count"];
                u.Email = w["email"].as_string();
            });
            return result;
        }
    }

    User updateUserDescription(const Api &api, const std::string &newDescription)
    {
        web::uri_builder builder("helix/users");

        builder.append_query("description", newDescription);

        auto result = api.reqWait().put(builder.to_uri(),AuthScope::USER_EDIT);

        if(result.has_field("data") && !result.at("data").is_null() && result.at("data").size() == 1)
        {
            auto data = result.at("data").as_array()[0];
            JsonWrapper w(data);

            User u;
            u.Login = w["login"].as_string();
            u.Email = w["email"].as_string();
            u.ViewCount = w["view_count"];
            u.OfflineImageUrl = w["offline_image_url"].as_string();
            u.AvatarUrl = w["profile_image_url"].as_string();
            u.Description = w["description"].as_string();
            u.BroadcaterType = BroadcasterType::fromString(w["broadcaster_type"].as_string());
            u.Type = UserType::fromString(w["type"].as_string());

            return u;
        }

        throw TwitchException("Response parsing error");
    }
}

