//
// Created by buran on 05/03/18.
//

#include <User.h>
#include <MakeRequest.h>
#include <Auth/UserAccessToken.h>
#include "TwitchException.h"
#include "JsonWrapper.h"

namespace TwitchXX
{
    User getUser(std::string id, std::string login)
    {
        if(!id.empty())
        {
            return getUsers({id}, {})[0];
        }
        else if(!login.empty())
        {
            return getUsers({}, {login})[0];
        }
        else
        {
            throw TwitchXX::TwitchException("Either login or user id should be specified!");
        }
    }

    std::vector<User> getUsers(std::vector<std::string> ids, std::vector<std::string> logins)
    {
        if(ids.empty() && logins.empty())
        {
            throw TwitchXX::TwitchException("Either login or user id should be specified!");
        }

        auto options = MakeRequest::getOptions();
        MakeRequest request(options);
        request.setAuthToken(std::make_shared<UserAccessToken>(options.at("token")));
        web::uri_builder builder("helix/users");

        addRangeOfParamsToBuilder(builder, "id", ids);
        addRangeOfParamsToBuilder(builder, "login", logins);

        auto response = request.get(builder.to_string());

        std::vector<User> result;

        if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());

            std::for_each(std::begin(data), std::end(data), [&](auto &&val)
            {
                JsonWrapper w(val);
                result.emplace_back();
                auto& u = result.back();
                u.Id = static_cast<std::string>(*w["id"]);
                u.Login = static_cast<std::string>(*w["login"]);
                u.DisplayName = static_cast<std::string>(*w["display_name"]);
                u.Type = UserType::fromString(*w["type"]);
                u.BroadcaterType = BroadcasterType::fromString(*w["broadcaster_type"]);
                u.Description = static_cast<std::string>(*w["description"]);
                u.AvatarUrl = static_cast<std::string>(*w["profile_image_url"]);
                u.OfflineImageUrl = static_cast<std::string>(*w["offline_image_url"]);
                u.ViewCount = *w["view_count"];
                u.Email = static_cast<std::string>(*w["email"]);
            });
            return result;
        }
    }
}

