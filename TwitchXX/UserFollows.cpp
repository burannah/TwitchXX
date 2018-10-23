//
// Created by buran on 12/03/18.
//

#include <UserFollows.h>
#include <TwitchException.h>
#include <Api.h>
#include <JsonWrapper.h>
#include <Utility.h>

namespace TwitchXX
{
    namespace
    {
        web::uri getUserFollowsUri(const UserFollowsOptions &options)
        {
            if( options.count > 100
                || (!options.after.empty() && !options.before.empty())
                || (options.from.empty() && options.to.empty()))
            {
                throw TwitchException("GetUserFollows: wrong input parameters");
            }

            web::uri_builder builder("helix/users/follows");
            if(!options.after.empty())
            {
                builder.append_query("after", options.after);
            }
            else if(!options.before.empty())
            {
                builder.append_query("before", options.before);
            }

            builder.append_query("first", options.count);

            if(!options.from.empty())
            {
                builder.append_query("from_id", options.from);
            }

            if(!options.to.empty())
            {
                builder.append_query("to_id", options.to);
            }

            return builder.to_uri();
        }

        UserFollow createUserFollow(const web::json::value& userFollow)
        {
            UserFollow u;
            JsonWrapper w(userFollow);

            u.from = w["from_id"];
            u.to = w["to_id"];
            u.since = DateFromString(w["followed_at"]);

            return u;
        }

    }

    std::tuple<std::vector<UserFollow>, unsigned long long, std::string>
    getUserFollows(const Api &api, const UserFollowsOptions &options)
    {


        auto response = api.reqWait().get(getUserFollowsUri(options));
        auto total = response.at("total").as_number().to_uint64();
        std::vector<UserFollow> result;

        if(response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& userFollow: data)
            {
                result.push_back(createUserFollow(userFollow));
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

        return std::make_tuple(result, total, new_cursor);
    };
}
