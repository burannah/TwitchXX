//
// Created by buran on 19/05/18.
//

#ifndef TWITCHXX_BITSLEADERBOARDOPTIONS_H
#define TWITCHXX_BITSLEADERBOARDOPTIONS_H

#include <PeriodType.h>
#include <TwitchDef.h>
#include "Api.h"

namespace TwitchXX
{
    /// Bits Leaderboard entries request parameters
    struct BitsLeaderboardOptions
    {
        int count = 10;                                     ///< Number of results to be returned. Maximum: 100. Default: 10.
        PeriodType::Value period = PeriodType::Value::ALL;  ///< Time period over which data is aggregated (PST time zone).
                                                            ///< This parameter interacts with started_at. Valid values
                                                            ///< are given below. Default: "all".
        Date started;                                       ///< Timestamp for the period over which the returned data is
                                                            ///< aggregated. If this is not provided, data is aggregated
                                                            ///< over the current period; e.g., the current day/week/month/year.
                                                            ///< This value is ignored if period is "all".
        unsigned long long  userId;                         ///< ID of the user whose results are returned;
                                                            ///< i.e., the person who paid for the bits.

    };
}

#endif //TWITCHXX_BITSLEADERBOARDOPTIONS_H
