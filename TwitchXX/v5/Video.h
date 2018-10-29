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
            double Chunked;
            double High;
            double Medium;
            double Low;
            double Mobile;

        };

        struct VideoResolution
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

            std::vector<Thumbnail> Large;
            std::vector<Thumbnail> Medium;
            std::vector<Thumbnail> Small;
            std::vector<Thumbnail> Template;
        };
        class Video
        {
        public:
            std::string      Id;
            unsigned long long BroadcasterId;
            VideoType::Value BroadcastType;
            unsigned long long ChannelId;
            Date             Created;
            std::string      Description;
            std::string      DescriptionHtml;
            FPS              Fps;
            std::string      Game;
            std::string      Language;
            int              Length;
            VideoPreview     Preview;
            Date             Published;
            VideoResolution  Resolution;
            std::string      Status;
            std::string      TagList;
            VideoThumb       Thumbnails;
            std::string      Title;
            std::string      Url;
            std::string      Viewable;
            Date             ViewedAt;
            unsigned long long Views;
            Date             Recorded;
            //Communities      Cmnty;  //TODO: Implement Communitites
            std::string      AnimatedPreviewUrl;
            std::string      SeekServiceUrl;
            std::string      IncrementViewCountUrl;
            std::string      Restriction;

        };
    }
}



#endif //TWITCHXX_VIDEO_H
