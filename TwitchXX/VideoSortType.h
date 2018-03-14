//
// Created by buran on 14/03/18.
//

#ifndef TWITCHXX_SORTTYPE_H
#define TWITCHXX_SORTTYPE_H

#include <string>

namespace TwitchXX
{
    ///Video request results sorting type
    class VideoSortType
    {
    public:
        /// Sorting types enum
        enum class Value
        {
            TIME,
            TRENDING,
            VIEWS
        };

        /// Video sort type enum value to string
        static std::string toString(VideoSortType::Value v);

        /// Sort type enum value from string
        static VideoSortType::Value  fromString(const std::string& s);

        /// Sort type enum value from int
        static VideoSortType::Value fromInt(int i);

    };
}



#endif //TWITCHXX_SORTTYPE_H
