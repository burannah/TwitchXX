//
// Created by buran on 05/03/18.
//

#ifndef TWITCHXX_BROADCASTERTYPE_H
#define TWITCHXX_BROADCASTERTYPE_H

#include <string>

namespace TwitchXX
{
    /// Broadcaster type enum class
    class BroadcasterType
    {
    public:
        ///Actual enum
        enum class Value
        {
            NONE,           //<
            PARTNER,
            AFFILIATE
        };

        //@{
        /// Helper functions
        static std::string toString(Value v); //< User type enum value to string

        static Value  fromString(const std::string& s); //< User type enum value from string

        static Value fromInt(int i); //< User type enum value from int
        //@}
    };
}

#endif //TWITCHXX_BROADCASTERTYPE_H
