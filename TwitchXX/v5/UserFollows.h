//
// Created by buran on 12/07/18.
//

#ifndef TWITCHXX_USERFOLLOWS_H
#define TWITCHXX_USERFOLLOWS_H

#include <string>
#include <vector>
#include <Api.h>
#include <v5/User.h>

namespace TwitchXX
{
    namespace v5
    {
        struct UserFollow
        {
            Date Since;
            bool Notifications;
            v5::User User;
        };

        std::tuple<std::vector<UserFollow>, uint64_t, std::string> getChannelFollowers(const Api &api,
                                                                                       std::string channelId,
                                                                                       std::optional<int> limit = std::nullopt,
                                                                                       const std::optional<std::string> &_cursor = std::nullopt);

        class UserFollows
        {
        private:
            int _limit = 1;
            uint64_t _size = 0;
            std::string _cursor;
            std::string _channelId;
            std::vector<UserFollow> _users;
            Api _api;
        public:
            UserFollows(const Api& api,
                        const std::string& channelId)
            :_channelId{channelId}
            ,_api{api}
            {};


            uint64_t size()
            {
                std::tie(std::ignore, _size, std::ignore) = getChannelFollowers(_api, _channelId);
                return _size;
            }

            uint64_t fetch(const std::optional<int> &limit)
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
                    _limit = newLimit;

                    std::tie(newFollows, _size, _cursor) = getChannelFollowers(_api, _channelId, _limit, _cursor);
                }
                else
                {
                    std::tie(newFollows, _size, _cursor) = getChannelFollowers(_api, _channelId, std::nullopt, _cursor);
                    _limit = std::min(100, _limit*2);
                }

                std::copy(std::begin(newFollows), std::end(newFollows), std::back_inserter(_users));
            }
        };


    }
}

#endif //TWITCHXX_USERFOLLOWS_H
