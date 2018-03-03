//
// Created by buran on 03/03/18.
//

#ifndef TWITCHXX_STREAMTYPE_H
#define TWITCHXX_STREAMTYPE_H

namespace TwitchXX
{
/***
 * Stream type enum & helpers
 */
    struct StreamType
    {
        /***
         * Stream types
         */
        enum class Value
        {
            ALL,
            LIVE,
            VODCAST,
            RERUN
        };

        /// Stream type enum value to string
        static std::string toString(StreamType::Value v);

        /// Stream type enum value from string
        static StreamType::Value  fromString(const std::string& s);

        /// Stream type enum value from int
        static StreamType::Value fromInt(int i);
    };

}

#endif //TWITCHXX_STREAMTYPE_H
