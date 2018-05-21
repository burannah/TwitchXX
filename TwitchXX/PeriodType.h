//
// Created by buran on 14/03/18.
//

#ifndef TWITCHXX_PERIODTYPE_H
#define TWITCHXX_PERIODTYPE_H

#include <string>

namespace TwitchXX
{
    ///Period type helper class
    class PeriodType
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
        static std::string toString(PeriodType::Value v);

        /// Period type enum value from string
        static PeriodType::Value  fromString(const std::string& s);

        /// Period type enum value from int
        static PeriodType::Value fromInt(int i);
    };
}


#endif //TWITCHXX_PERIODTYPE_H
