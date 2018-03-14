//
// Created by buran on 14/03/18.
//

#ifndef TWITCHXX_VIDEOTYPE_H
#define TWITCHXX_VIDEOTYPE_H

#include <string>

namespace TwitchXX
{
    /// Video type helper class
    class VideoType
    {
    public:

        ///Video type enum class
        enum class Value
        {
            ALL,
            UPLOAD,
            ARCHIVE,
            HIGHLIGHT
        };

        /// Video type enum value to string
        static std::string toString(VideoType::Value v);

        /// Video type enum value from string
        static VideoType::Value  fromString(const std::string& s);

        /// Video type enum value from int
        static VideoType::Value fromInt(int i);

    };
}


#endif //TWITCHXX_VIDEOTYPE_H
