//
// Created by buran on 7/28/18.
//

#ifndef TWITCHXX_DIRECTION_H
#define TWITCHXX_DIRECTION_H

#include <string>

namespace TwitchXX
{
    class Direction
    {
    public:
        enum class Value
        {
            ASC,
            DESC
        };

        static Value fromString(const std::string& s);
        static std::string toString(Value v);

    };
}


#endif //TWITCHXX_DIRECTION_H
