//
// Created by buran on 19/05/18.
//

#include <BitsLeaderboardEntry.h>
#include <BitsLeaderboardOptions.h>
#include <Log.h>
#include <TwitchException.h>
#include <Utility.h>
#include <JsonWrapper.h>

namespace TwitchXX
{
    std::vector<BitsLeaderboardEntry>
    getBitsLeaderborard(const Api &api, const BitsLeaderboardOptions &opt)
    {
        if (opt.count > 100 || opt.count < 1)
        {
            const std::string err = "getBitsLeaderborard: count must be not greater then 100.";
            Log::Error(err);
            throw TwitchException(err.c_str());
        }

        web::uri_builder builder("helix/bits/leaderboard");
        builder.append_query("count", opt.count);
        builder.append_query("period", PeriodType::toString(opt.period));
        if(opt.period != PeriodType::Value::ALL)
        {
            builder.append_query("started_at", DateToString);
        }

        if(opt.userId)
        {
            builder.append_query("user_id", opt.userId);
        }


        auto response = api.reqWait().get(builder.to_uri(), AuthScope::BITS_READ);
        std::vector<BitsLeaderboardEntry> result;

        if (response.has_array_field("data"))
        {
            auto data = response.at("data").as_array();

            result.reserve(data.size());
            for(const auto& entry: data)
            {
                JsonWrapper w(entry);

                result.emplace_back(w["user_id"], w["rank"],  w["score"]);
            }
        }

        return result;
    }
}


