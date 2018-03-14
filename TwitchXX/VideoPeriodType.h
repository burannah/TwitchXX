//
// Created by buran on 14/03/18.
//

#ifndef TWITCHXX_PERIODTYPE_H
#define TWITCHXX_PERIODTYPE_H

#include <string>

namespace TwitchXX
{
    ///Period type helper class
    class VideoPeriodType
    {
    public:

        /// Period types values
        enum class Value
        {
            ALL,
            DAY,
            WEEK,
            MONTH
        };

        /// Period type enum value to string
        static std::string toString(VideoPeriodType::Value v);

        /// Period type enum value from string
        static VideoPeriodType::Value  fromString(const std::string& s);

        /// Period type enum value from int
        static VideoPeriodType::Value fromInt(int i);
    };
}


#endif //TWITCHXX_PERIODTYPE_H
