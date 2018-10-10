//
// Created by buran on 12/07/18.
//

#include "UserFollows.h"
#include <JsonWrapper.h>
#include <v5/Create.h>

namespace TwitchXX
{
    namespace v5
    {
        namespace
        {
            web::uri_builder createGetChannelFollowersBuilder(const std::string& channelId,
                                                              const std::optional<int> limit,
                                                              const std::optional<std::string>& cursor)
            {
                web::uri_builder builder("kraken/channels");
                builder.append_path(channelId);
                builder.append_path("follows");

                if(limit)
                {
                    builder.append_query("limit",limit.value());
                }

                if(cursor)
                {
                    builder.append_query("cursor", cursor.value());
                }

                return builder;
            }
        }

        UserFollow createUserFollow(const web::json::value &value)
        {
            UserFollow u;
            JsonWrapper w(value);

            u.Since = w["created_at"];
            u.Notifications = w["notifications"];
            u.User = createUser(value.at("user"));

            return u;
        }

        std::tuple<std::vector<UserFollow>, uint64_t, std::string>
        getChannelFollowers(const Api &api,
                            const std::string& channelId,
                            const std::optional<int>& limit,
                            const std::optional<std::string> &cursor)
        {
            auto response = api.reqOnce().get(createGetChannelFollowersBuilder(channelId, limit, cursor).to_uri());

            std::string newCursor = response.at("_cursor").as_string();
            uint64_t size = response.at("_total").as_number().to_uint64();
            std::vector<UserFollow> result;

            if(response.has_field("follows") && response.at("follows").is_array())
            {
                auto rawFollows = response.at("follows").as_array();

                for(auto&& follow: rawFollows)
                {
                    result.push_back(createUserFollow(follow));
                }
            }

            return std::make_tuple(result, size, newCursor);
        }

        uint64_t UserFollows::fetch(const std::optional<int> &limit)
        {
            std::vector<UserFollow> newFollows;
            if(_cursor.empty())
            {
                std::tie(newFollows, _size, _cursor) = getChannelFollowers(_api,_channelId, limit.value_or(_limit));
            }
            else if(limit)
            {
                auto newLimit = limit.value() > 100 ? 100 : limit.value();
                newLimit = std::max(_limit, newLimit);
                if(newLimit <= _limit)
                {
                    return _size;
                }
                else
                {
                    _limit = newLimit;
                }

                std::tie(newFollows, _size, _cursor) = getChannelFollowers(_api, _channelId, _limit, _cursor);
            }
            else
            {
                if(_limit < 100)
                {
                    _limit = std::min(100, _limit*2);
                    std::tie(newFollows, _size, _cursor) = getChannelFollowers(_api, _channelId, std::nullopt, _cursor);
                }
                else
                {
                    std::tie(newFollows, _size, _cursor) = getChannelFollowers(_api, _channelId, std::nullopt, _cursor);
                }
            }

            std::copy(std::begin(newFollows), std::end(newFollows), std::back_inserter(_users));
        }

        UserFollow &UserFollows::at(size_t index)
        {
            if(!_size)
            {
                fetch(index+1);
            }

            if(_size <= index)
            {
                throw std::out_of_range(std::string("Index is out of range: ") + std::to_string(index));
            }

            while(index < _size && index >= _users.size())
            {
                fetch(std::nullopt);
            }

            return _users[index];
        }
    }
}