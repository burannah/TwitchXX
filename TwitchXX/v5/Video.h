//
// Created by buran on 10/25/18.
//

#ifndef TWITCHXX_VIDEO_H
#define TWITCHXX_VIDEO_H

#include <string>

#include <TwitchDef.h>
#include <VideoType.h>

namespace TwitchXX
{
    namespace v5
    {
        struct FPS
        {
            std::string Chunked;
            std::string High;
            std::string Medium;
            std::string Low;
            std::string Mobile;

        };

        struct VideoPreview
        {
            std::string Large;
            std::string Medium;
            std::string Small;
            std::string Temlate;
        };

        struct VideoThumb
        {
            struct Thumbnail
            {
                std::string Type;
                std::string Url;
            };

            Thumbnail Large;
            Thumbnail Medium;
            Thumbnail Small;
            Thumbnail Template;
        };
        class Video
        {
        public:
            std::string      Id;
            std::string      BroadcasterId;
            VideoType::Value BroadcastType;
            std::string      ChannelId;
            Date             Created;
            std::string      Description;
            std::string      DescriptionHtml;
            FPS              Fps;
            std::string      Game;
            std::string      Language;
            int              Length;
            VideoPreview     Preview;
            Date             Published;
            FPS              Resolution;
            std::string      Status;
            std::string      TagList;
            VideoThumb       Thumbnails;
            std::string      Title;
            std::string      Url;
            std::string      Viewable;
            Date             ViewedAt;
            unsigned long long Views;
        };
    }
}



#endif //TWITCHXX_VIDEO_H
