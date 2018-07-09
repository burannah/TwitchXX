//
// Created by buran on 05/07/18.
//

#ifndef TWITCHXX_FEEDPOST_H
#define TWITCHXX_FEEDPOST_H

#include <string>
#include <optional>
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
            CAN_REPLY = 4,
            CAN_SHARE = 8
        };

        Permission fromString(const std::string& s);

        Permission  operator|(const Permission& lhs, const Permission& rhs);
        Permission& operator|=(Permission& lhs, const Permission& rhs);

        class Emote
        {
        public:
            unsigned long long End;
            unsigned long long Id;
            unsigned long long Set;
            unsigned long long Start;
        };

        class Reaction
        {
        public:
            std::string Set;
            unsigned long long     Count;
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
            User                  Author;
        };
        class FeedPost
        {
        public:
            std::string              Body;
            std::vector<FeedComment> Comments;
            Date                     Created;
            bool                     Deleted;
            //std::vector<??>        Embeds;
            std::vector<Emote>       Emotes;
            std::string              Id;
            Permission               Permissions;
            std::vector<Reaction>    Reactions;
            User                     Author;
        };

        FeedPost getPost(const Api &api, std::string channelId, std::string postId, int count = 0);

        std::tuple<std::vector<FeedPost>, std::string>
        getPosts(const Api &api,
                 const std::string &channelId,
                 int limit = 100,
                 const std::optional<std::string> &cursor = std::nullopt,
                 int comments = 5);
    }
}


#endif //TWITCHXX_FEEDPOST_H
