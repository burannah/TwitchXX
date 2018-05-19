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

    /// Video desriptor class
    class Video
    {
    public:
        unsigned long long Id;              ///< Id
        unsigned long long UserId;          ///< Video's user id
        std::string        Title;           ///< Title
        std::string        Description;     ///< Description
        Date               Created;         ///< Created
        Date               Published;       ///< Published
        std::string        ThumbnailUrl;    ///< Video's thumbnail URL
        unsigned long long ViewCount;       ///< View count
        std::string        Language;        ///< Language
        std::string        Duration;        ///< Duration
    };

    std::tuple<std::vector<Video>, std::string> getVideos(const Api& api,
                                                          const std::vector<uint64_t>& ids,
                                                          uint64_t userId = 0,
                                                          uint64_t gameId = 0,
                                                          const VideoOptions& opt = {});

}




#endif //TWITCHXX_VIDEO_H
