//
// Created by buran on 14/03/18.
//

#ifndef TWITCHXX_VIDEO_H
#define TWITCHXX_VIDEO_H

#include <string>
#include <TwitchDef.h>


namespace TwitchXX
{
    class VideoOptions;
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
                                                          const std::vector<u_int64_t>* ids,
                                                          const u_int64_t* userId = nullptr,
                                                          const u_int64_t* gameId = nullptr,
                                                          const VideoOptions* opt = nullptr);

}




#endif //TWITCHXX_VIDEO_H
