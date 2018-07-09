//
// Created by buran on 05/07/18.
//

#include <v5/FeedPost.h>

#include <JsonWrapper.h>
#include <Utility.h>
#include <TwitchException.h>
#include <Log.h>

#include <cpprest/json.h>
#include <iterator>
#include <optional>


namespace TwitchXX
{
    namespace v5
    {
        namespace
        {
            Emote createEmote(const web::json::value &rawEmote)
            {
                Emote e;
                JsonWrapper w(rawEmote);

                e.End = *w["end"];
                e.Id = *w["id"];
                e.Set = *w["set"];
                e.Start = *w["start"];

                return e;
            }

            User createUser(const web::json::value &rawUser)
            {
                User u;
                if(!rawUser.is_null() && rawUser.is_object())
                {
                    JsonWrapper w(rawUser);
                    u.Id = w["_id"]->as_string();
                    u.Bio = w["bio"]->as_string();
                    u.Created = DateFromString(*w["created_at"]);
                    u.DisplayName = w["display_name"]->as_string();
                    u.Logo = w["logo"]->as_string();
                    u.Name = w["name"]->as_string();
                    u.Type = w["type"]->as_string();
                    u.Updated = DateFromString(*w["updated_at"]);
                }
                return u;
            }

            std::vector<Emote> createEmotes(const web::json::value &rawPost)
            {
                std::vector<Emote> result;
                if(rawPost.has_field("emotes")
                   && rawPost.at("emotes").is_array()
                   && rawPost.at("emotes").as_array().size())
                {
                    const auto& emotes = rawPost.at("emotes").as_array();
                    for_each(std::begin(emotes), std::end(emotes), [&](const auto& emote)
                    {
                        result.push_back(createEmote(emote));
                    });
                }
                return result;
            }

            Permission createPermission(const web::json::value &rawPost)
            {
                Permission p = Permission::NONE;
                if(rawPost.has_field("permissions") && rawPost.at("permissions").is_object())
                {
                    const auto& obj = rawPost.at("permissions").as_object();
                    for_each(obj.begin(), obj.end(), [&](const auto& item)
                    {
                        if(item.second.is_boolean() && item.second.as_bool())
                        {
                            p |= fromString(item.first);
                        }
                    });
                }
                return p;
            }

            std::vector<Reaction> createReactions(const web::json::value &rawPost)
            {
                std::vector<Reaction> result;
                if(rawPost.has_field("reactions") && rawPost.at("reactions").is_object())
                {
                    const auto& reactions = rawPost.at("reactions").as_object();
                    for_each(reactions.begin(), reactions.end(), [&](const auto& reaction)
                    {
                        Reaction r;
                        r.Set = reaction.first;
                        r.Count = reaction.second.at("count").as_number().to_int64();
                        r.Emote = reaction.second.at("emote").as_string();
                        r.Users = JsonWrapper(reaction.second)["user_ids"]->as_vector();
                        result.push_back(r);
                    });
                }
                return result;
            }

            FeedComment createComment(const web::json::value &rawComment)
            {
                FeedComment c;
                JsonWrapper w(rawComment);

                c.Body = w["body"]->as_string();
                c.Created = DateFromString(*w["created_at"]);
                c.Deleted = *w["deleted"];
                c.Emotes = createEmotes(rawComment);
                c.Id = w["id"]->as_string();
                c.Permissions = createPermission(rawComment);
                c.Reactions = createReactions(rawComment);
                c.Author = createUser(rawComment.at("user"));

                return c;
            }

            std::vector<FeedComment> createComments(const web::json::value &rawPost)
            {
                std::vector<FeedComment> result;
                if(rawPost.has_field("comments")
                   && rawPost.at("comments").has_field("_total")
                   && rawPost.at("comments").at("_total").as_number().to_int64() > 0)
                {
                    const auto& comments = rawPost.at("comments").at("comments").as_array();
                    for_each(std::begin(comments), std::end(comments), [&](const auto& comment)
                    {
                        result.push_back(createComment(comment));
                    });
                }
                return result;
            }

            FeedPost createPost(const web::json::value& rawPost)
            {
                FeedPost p;
                JsonWrapper j(rawPost);

                p.Body = j["body"]->as_string();

                p.Comments = createComments(rawPost);

                p.Created = TwitchXX::DateFromString(*j["created_at"]);
                p.Deleted = *j["deleted"];
                //p.Embeds ??
                p.Emotes = createEmotes(rawPost);

                p.Id = j["id"]->as_string();
                p.Permissions = createPermission(rawPost);

                p.Reactions = createReactions(rawPost);

                p.Author = createUser(rawPost.at("user"));

                return p;
            }

        }

        FeedPost getPost(const Api &api, std::string channelId, std::string postId, int count)
        {
            web::uri_builder builder("kraken/feed");
            builder.append_path(channelId);
            builder.append_path("posts");
            builder.append_path(postId);

            builder.append_query("comments", count);
            auto response = api.reqWait().get(builder.to_uri());

            return createPost(response);
        }

        Permission fromString(const std::string &s)
        {
            if(s.empty())
            {
                return Permission::NONE;
            }
            else if(s == "can_delete")
            {
                return Permission::CAN_DELETE;
            }
            else if(s == "can_moderate")
            {
                return Permission::CAN_MODERATE;
            }
            else if(s == "can_reply")
            {
                return Permission::CAN_REPLY;
            }
            else if(s == "can_share")
            {
                return Permission::CAN_SHARE;
            }
            else
            {
                const std::string error = "Unsupported Permission type: " + s;
                Log::Error(error);
                throw TwitchXX::TwitchException(error.c_str());
            }
        }

        Permission &operator|=(Permission &lhs, const Permission &rhs)
        {
            lhs = lhs | rhs;
            return lhs;
        }

        Permission operator|(const Permission &lhs, const Permission &rhs)
        {
            return static_cast<Permission>(
                    static_cast<std::underlying_type_t<Permission>>(lhs)
                    | static_cast<std::underlying_type_t<Permission>>(rhs));
        }

        std::tuple<std::vector<FeedPost>, std::string>
        getPosts(const Api &api,
                 const std::string &channelId,
                 int limit,
                 const std::optional<std::string> &cursor,
                 int comments)
        {
            web::uri_builder builder("kraken/feed");
            builder.append_path(channelId);
            builder.append_path("posts");
            builder.append_query("limit", limit);
            builder.append_query("comments", comments);
            if(cursor)
            {
                builder.append_query("cursor", cursor.value());
            }

            auto response = api.reqOnce().get(builder.to_uri());

            JsonWrapper w(response);

            if(w["_disabled"]->as_bool())
            {
                return std::tuple<std::vector<FeedPost>, std::string>();
            }

            std::string resultCursor = w["_cursor"]->as_string();
            std::vector<FeedPost> result;
            if(response.has_field("posts") && response.at("posts").is_array() && response.at("posts").as_array().size())
            {
                auto posts = response.at("posts").as_array();

                std::for_each(std::begin(posts), std::end(posts),[&](const auto& rawPost)
                {
                    result.push_back(createPost(rawPost));
                });
            }

            return std::make_tuple(result, resultCursor);
        }
    }
}

