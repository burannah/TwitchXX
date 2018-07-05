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


namespace TwitchXX
{
    namespace v5
    {
        namespace
        {
            FeedPost createPost(const web::json::value& rawPost)
            {
                FeedPost p;
                JsonWrapper j(rawPost);

                p.Body = *j["body"];

                if(rawPost.has_field("comments")
                && rawPost.at("commetns").has_field("_total")
                && rawPost.at("comments").at("_total").as_number().to_int64() > 0)
                {
                    const auto& comments = rawPost.at("comments").at("comments").as_array();
                    std::for_each(std::begin(comments), std::end(comments),[&](const auto& comment)
                    {
                        p.Comments.push_back(createComment(comment));
                    });
                }

                p.Created = TwitchXX::DateFromString(*j["created_at"]);
                p.Deleted = *j["deleted"];
                //Embeds

                if(rawPost.has_field("emotes")
                && rawPost.at("emotes").is_array()
                && rawPost.at("emotes").as_array().size())
                {
                    const auto& emotes = rawPost.at("emotes").as_array();
                    std::for_each(std::begin(emotes), std::end(emotes), [&](const auto& emote)
                    {
                        p.Emotes.push_back(createEmote(emote));
                    });
                }

                p.Id = *j["id"];
                if(rawPost.has_field("permissions") && rawPost.at("permissions").is_object())
                {
                    p.Permissions = Permission::NONE;
                    const auto& obj = rawPost.at("permissions").as_object();
                    std::for_each(obj.begin(), obj.end(), [&](const auto& p)
                    {
                        if(p.second.as_bool())
                        {
                            p.Permission |= fromString(p.first);
                        }
                    });
                }

                if(rawPost.has_field("reactions") && rawPost.at("reactions").is_object())
                {
                    const auto& reactions = rawPost.at("reactions").as_object();
                    std::for_each(reactions.begin(), reactions.end(), [&](const auto& reaction)
                    {
                        Reaction r;
                        r.Set = reaction.first;
                        r.Count = reaction.second.at("count").as_number().as_int64();
                        r.Emote = reaction.second.at("emote").as_string();
                        r.Users = JsonWrapper(reaction.second)["user_ids"]->as_vector();
                    });
                }

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
            } else
            {
                const std::string error = "Unsupported Permission type: " + s;
                Log::Error(error);
                throw TwitchXX::TwitchException(error.c_str());
            }
        }
    }
}

