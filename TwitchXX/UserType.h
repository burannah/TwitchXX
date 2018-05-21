//
// Created by buran on 05/03/18.
//

#ifndef TWITCHXX_USERTYPE_H
#define TWITCHXX_USERTYPE_H

#include <string>

namespace TwitchXX
{
    /// User type enum class
    class UserType
    {
    public:
        ///Actual enum
        enum class Value
        {
            NONE,
            STAFF,
            ADMIN,
            GLOBAL_MOD
        };
        //@{
        /// Helper functions
        static std::string toString(Value v);           //< User type enum value to string

        static Value  fromString(const std::string& s); //< User type enum value from string

        static Value fromInt(int i);                    //< User type enum value from int
        //@}
    };
}



#endif //TWITCHXX_USERTYPE_H
