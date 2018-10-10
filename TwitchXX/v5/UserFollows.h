#include <utility>

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
                                                                                       const std::string& channelId,
                                                                                       const std::optional<int>& limit = std::nullopt,
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
            UserFollows(Api api,
                        std::string channelId)
            :_channelId{std::move(channelId)}
            ,_api{std::move(api)}
            {};

            uint64_t size()
            {
                if(!_size)
                {
                    fetch(100);
                }

                return _size;
            }

            uint64_t fetch(const std::optional<int> &limit);

            UserFollow& at(size_t index);
        };


    }
}

#endif //TWITCHXX_USERFOLLOWS_H
