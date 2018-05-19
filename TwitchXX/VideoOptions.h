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
    struct VideoOptions
    {
        std::string            After;
        std::string            Before;
        size_t                 Count;
        std::string            Language;
        PeriodType::Value Period;
        VideoSortType::Value   Sort;
        VideoType::Value       Type;

    };

}

#endif //TWITCHXX_VIDEOOPTIONS_H
