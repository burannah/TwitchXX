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
    std::tuple<std::vector<UserFollow>, unsigned long long, std::string>
    getUserFollows(const Api &api, const UserFollowsOptions &options)
    {
        if( options.count > 100
            || (!options.after.empty() && !options.before.empty())
            || (options.from.empty() && options.to.empty()))
        {
            throw TwitchXX::TwitchException("GetUserFollows: wrong input parameters");
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

        auto response = api.reqWait().get(builder.to_uri());
        auto total = response.at("total").as_number().to_uint64();
        std::vector<UserFollow> result;

        if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            std::for_each(std::begin(data), std::end(data), [&](auto&& val)
            {
                result.emplace_back();
                auto& u = result.back();
                JsonWrapper w(val);

                u.from = *w["from_id"];
                u.to = *w["to_id"];
                u.since = DateFromString(*w["followed_at"]);
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

        return std::make_tuple(result, total, new_cursor);
    };
}
