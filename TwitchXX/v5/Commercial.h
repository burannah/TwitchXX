//
// Created by buran on 10/29/18.
//

#ifndef TWITCHXX_COMMERCIAL_H
#define TWITCHXX_COMMERCIAL_H

#include <string>

namespace TwitchXX
{
    namespace v5
    {
        enum class CommercialLength
        {
            COMMERCIAL_30 = 30,
            COMMERCIAL_60 = 60,
            COMMERCIAL_90 = 90,
            COMMERCIAL_120 = 120,
            COMMERCIAL_150 = 150,
            COMMERCIAL_180 = 180
        };

        struct Commercial
        {
            int Length;
            std::string Message;
            int Retry;
        };
    }

};


#endif //TWITCHXX_COMMERCIAL_H
