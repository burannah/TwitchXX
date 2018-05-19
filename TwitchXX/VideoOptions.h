//
// Created by buran on 14/03/18.
//

#ifndef TWITCHXX_VIDEOOPTIONS_H
#define TWITCHXX_VIDEOOPTIONS_H

#include <string>
#include <PeriodType.h>
#include <VideoSortType.h>
#include <VideoType.h>
#include <vector>
#include "Api.h"

namespace TwitchXX
{
    /// Options class for getVideos request
    struct VideoOptions
    {
        std::string            After;       ///< After (forward) cursor
        std::string            Before;      ///< Before (backward) cursor
        size_t                 Count;       ///< Maximum number of fetched videos per request
        std::string            Language;    ///< Video's language
        PeriodType::Value      Period;      ///< Period to search
        VideoSortType::Value   Sort;        ///< Sort type
        VideoType::Value       Type;        ///< Video type
    };
}

#endif //TWITCHXX_VIDEOOPTIONS_H
