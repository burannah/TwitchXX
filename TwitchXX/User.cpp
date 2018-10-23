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
    namespace
    {
        web::uri getUsersUri(const std::vector<std::string> &ids,
                             const std::vector<std::string> &logins)
        {
            web::uri_builder builder("helix/users");

            addRangeOfParamsToBuilder(builder, "id", ids);
            addRangeOfParamsToBuilder(builder, "login", logins);

            return builder.to_uri();
        }

        User createUser(const web::json::value &user)
        {
            JsonWrapper w(user);

            User u;
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

            return u;
        }
    }

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
            throw TwitchException("Either login or user id should be specified!");
        }
    }

    std::vector<User> getUsers(const Api &api,
                               const std::vector<std::string> &ids,
                               const std::vector<std::string> &logins)
    {
        if(ids.empty() && logins.empty())
        {
            throw TwitchException("Either login or user id should be specified!");
        }

        auto response = api.reqWait().get(getUsersUri(ids, logins));

        std::vector<User> result;

        if(response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());

            for(const auto& user: data)
            {
                result.push_back(createUser(user));

            }
            return result;
        }
    }

    User updateUserDescription(const Api &api, const std::string &newDescription)
    {
        web::uri_builder builder("helix/users");

        builder.append_query("description", newDescription);

        auto result = api.reqWait().put(builder.to_uri(),AuthScope::USER_EDIT);

        if(result.has_array_field("data"))
        {
            return createUser(result.at("data").as_array()[0]);
        }

        throw TwitchException("Response parsing error");
    }
}

