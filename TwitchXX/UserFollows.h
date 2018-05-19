//
// Created by buran on 12/03/18.
//

#ifndef TWITCHXX_USERFOLLOWS_H
#define TWITCHXX_USERFOLLOWS_H

#include <tuple>
#include <vector>
#include <TwitchDef.h>

namespace TwitchXX
{
    class Api;

    /// Get user follows request options
    struct UserFollowsOptions
    {
        std::string after;      ///< 'next' - cursor
        std::string before;     ///< 'prev' - cursor
        size_t      count = 20; ///< maximum number of objects per response (Max - 100)
        std::string from;       ///< get the information about which are followed by 'from` user id
        std::string to;         ///< get the information about which users are following 'to' user id
    };

    /// User follow information
    struct UserFollow
    {
        unsigned long long from = 0; ///< Following from user
        unsigned long long to = 0;   ///< Following to user
        Date               since;    ///< Date of following

    };

    /***
     * Get user folllows request. With all the options.
     * @param api     Twitch API object to use request, auth e.t.c.
     * @param options UserFollowsOptions request
     * @return a tuple with first element - a vector of followers/followed user ids,
     *         second - total number of results, third - cursor
     */
    std::tuple<std::vector<UserFollow>, unsigned long long,  std::string>
    getUserFollows(const Api& api, const UserFollowsOptions& options);



}


#endif //TWITCHXX_USERFOLLOWS_H
