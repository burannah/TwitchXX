//
// Created by buran on 19/05/18.
//

#ifndef TWITCHXX_BITSLEADERBOARDENTRY_H
#define TWITCHXX_BITSLEADERBOARDENTRY_H

#include <vector>
#include <string>
#include <Api.h>

namespace TwitchXX
{
    class BitsLeaderboardOptions;

    /// Bits leaderboard entry record
    struct BitsLeaderboardEntry
    {
        BitsLeaderboardEntry(unsigned long long user, unsigned long long rnk,  unsigned long long scr)
        : userId(user)
        , rank(rnk)
        , score(scr)
        {}
        unsigned long long userId;
        unsigned long long rank;
        unsigned long long score;
    };

    /**
    *****************************************************************************************
    *  @brief      Request Bits Leaderboard
    *  @details    Get a number (up to 100) of bits leaderboard entries
    *  @param      api - API object  providing request and auth objects
    *  @param      opt - request parameters
    *  @return     a vector of TwitchXX::BitsLeaderboard objects (if any were found).
    ****************************************************************************************/
    std::vector<BitsLeaderboardEntry>
            getBitsLeaderborard(const Api &api,
                                const BitsLeaderboardOptions &opt);
}

#endif //TWITCHXX_BITSLEADERBOARDENTRY_H
