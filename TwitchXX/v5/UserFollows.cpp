//
// Created by buran on 12/07/18.
//

#include "UserFollows.h"

namespace TwitchXX
{
    namespace v5
    {
        std::tuple<std::vector<UserFollow>, uint64_t, std::string> getChannelFollowers(const Api &api,
                                                                                       std::string channelId,
                                                                                       std::optional<int> limit,
                                                                                       const std::optional<std::string> &_cursor)
        {
            return std::tuple<std::vector<UserFollow>, uint64_t, std::string>();
        }
    }
}