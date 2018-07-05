//
// Created by buran on 05/07/18.
//

#ifndef TWITCHXX_FEEDPOST_H
#define TWITCHXX_FEEDPOST_H

#include <string>
#include <TwitchDef.h>
#include <Api.h>
#include "User.h"

namespace TwitchXX
{
    namespace v5
    {
        enum class Permission
        {
            NONE = 0,
            CAN_DELETE = 1,
            CAN_MODERATE = 2,
            CAN_REPLY = 4
        };

        Permission fromString(const std::string& s);

        class Emote
        {
            int64_t End;
            int64_t In;
            int64_t Set;
            int64_t Start;
        };

        class Reaction
        {
        public:
            std::string Set;
            int64_t     Count;
            std::string Emote;
            std::vector<std::string> Users;
        };

        class FeedComment
        {
        public:
            std::string           Body;
            TwitchXX::Date        Created;
            bool                  Deleted;
            std::vector<Emote>    Emotes;
            std::string           Id;
            Permission            Permissions;
            std::vector<Reaction> Reactions;
            User                Author
        };
        class FeedPost
        {
        public:
            std::string Body;
            std::vector<FeedComment> Comments;
            Date        Created;
            bool        Deleted;
            //std::vector<??> Embeds;
            std::vector<Emote> Emotes;
            std::string Id;
            Permission  Permissions;
            User        Author;
        };

        FeedPost getPost(const Api &api, std::string channelId, std::string postId, int count = 0);
    }
}


#endif //TWITCHXX_FEEDPOST_H
