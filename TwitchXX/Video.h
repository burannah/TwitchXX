//
// Created by buran on 14/03/18.
//

#ifndef TWITCHXX_VIDEO_H
#define TWITCHXX_VIDEO_H

#include <string>
#include <TwitchDef.h>
#include <VideoOptions.h>


namespace TwitchXX
{
    class Api;

    class Video
    {
    public:
        unsigned long long Id;
        unsigned long long UserId;
        std::string        Title;
        std::string        Description;
        Date               Created;
        Date               Published;
        std::string        ThumbnailUrl;
        unsigned long long ViewCount;
        std::string        Language;
        std::string        Duration;
    };

    std::tuple<std::vector<Video>, std::string> getVideos(const Api& api,
                                                          const std::vector<uint64_t>& ids,
                                                          uint64_t userId = 0,
                                                          uint64_t gameId = 0,
                                                          const VideoOptions& opt = {});

}




#endif //TWITCHXX_VIDEO_H
