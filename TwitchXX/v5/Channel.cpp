//
// Created by buran on 09/07/18.
//

#include <JsonWrapper.h>
#include <BroadcasterType.h>
#include <TwitchException.h>
#include "Channel.h"
#include <v5/Create.h>
#include <VideoOptions.h>
#include <v5/Video.h>

namespace TwitchXX
{
    namespace v5
    {
        namespace
        {
            const int DEFAULT_LIMIT = 25;
            const int DEFAULT_OFFSET = 0;
            const Direction::Value DEFAULT_DIRECTION = Direction::Value::ASC;
            const int DEFAULT_COUNT = 10;
            const VideoType::Value DEFAULT_VIDEO_TYPE = VideoType::Value::ALL;
            const VideoSortType::Value DEFAULT_VIDEO_SORT_TYPE = VideoSortType::Value::TIME;

            Channel createChannel(const web::json::value &raw)
            {
                Channel c;

                if(raw.has_string_field("name"))
                {
                    JsonWrapper w(raw);
                    c.Mature = w["mature"];
                    c.Status = w["status"].as_string();
                    c.BroadcasterLang = w["broadcaster_language"].as_string();
                    c.GameName = w["game"].as_string();
                    c.Language = w["language"].as_string();
                    c.Id = w["_id"].as_string();
                    c.Name = w["name"].as_string();
                    c.Created = w["created_at"];
                    c.Updated = w["updated_at"];
                    c.Partner = w["partner"];
                    c.Logo = w["logo"].as_string();
                    c.VideoBanner = w["video_banner"].as_string();
                    c.ProfileBanner = w["profile_banner"].as_string();
                    c.ProfileBannerBkColor = w["profile_banner_background_color"].as_string();
                    c.Url = w["url"].as_string();
                    c.Views = w["views"];
                    c.Followers = w["followers"];
                    c.BroadcasterType = BroadcasterType::fromString(w["broadcaster_type"]);
                    c.Key = w["stream_key"].as_string();
                    c.Email = w["email"].as_string();
                }

                return c;
            }

            web::uri getChannelSubscriptionsUri(const std::string& channelId,
                                                int limit ,
                                                int offset,
                                                Direction::Value direction = Direction::Value::ASC)
            {
                if(channelId.empty())
                {
                    throw TwitchException("GetChannelSubscriptionsUri: channelId can not be empty");
                }

                if(limit > 100 || limit < 1)
                {
                    throw TwitchException("GetChannelSubscriptionsUri: limit value is out of range");
                }

                web::uri_builder builder("kraken/channels/" + channelId + "/subscriptions");

                if(limit != DEFAULT_LIMIT)
                {
                    builder.append_query("limit", limit);
                }
                if(offset != DEFAULT_OFFSET)
                {
                    builder.append_query("offset", offset);
                }
                if(direction != DEFAULT_DIRECTION)
                {
                    builder.append_query("direction", Direction::toString(direction));
                }

                return builder.to_uri();
            }

            Team createTeam(const web::json::value &rawTeam)
            {
                Team t;
                JsonWrapper j{rawTeam};

                t.Id = j["_id"];
                t.Background = j["background"].as_string();
                t.Banner = j["logo"].as_string();
                t.Created = j["created_at"];
                t.DisplayName = j["display_name"].as_string();
                t.Info = j["info"].as_string();
                t.Logo = j["logo"].as_string();
                t.Name = j["name"].as_string();
                t.Updated = j["updated_at"];
                return t;
            }

            web::uri getChannelVideosUri(const std::string& channelId, const VideoOptions* opt)
            {
                web::uri_builder builder("kraken/channels/" + channelId + "/videos");

                if(opt)
                {
                    if(opt->Count < 1 || opt->Count > 100)
                    {
                        throw TwitchException("getChannelVideosUri: count is out of range");
                    }

                    if(opt->Count != DEFAULT_COUNT)
                    {
                        builder.append_query("limit", opt->Count);
                    }

                    if(opt->Offset != DEFAULT_OFFSET)
                    {
                        builder.append_query("offset", opt->Offset);
                    }

                    for(const auto& type: opt->Type)
                    {
                        builder.append_query("broadcast_type", VideoType::toString(type));
                    }

                    if(!opt->Language.empty())
                    {
                        builder.append_query("language", opt->Language);
                    }
                    if(opt->Sort != DEFAULT_VIDEO_SORT_TYPE)
                    {
                        builder.append_query("sort", VideoSortType::toString(opt->Sort));
                    }

                    return builder.to_uri();

                }

            }

            FPS createFps(const web::json::value& rawFps)
            {
                FPS f;
                JsonWrapper w(rawFps);

                f.Chunked = w["chunked"].as_string();
                f.High = w["high"].as_string();
                f.Medium = w["medium"].as_string();
                f.Mobile = w["mobile"].as_string();
            }

            VideoPreview createPreview(const web::json::value& rawPreview)
            {
                VideoPreview v;
                JsonWrapper w(rawPreview);

                v.Medium = w["medium"].as_string();
                v.Large = w["large"].as_string();
                v.Small = w["small"].as_string();
                v.Temlate = w["template"].as_string();

                return v;
            }

            VideoThumb::Thumbnail createThumb(const std::string& name, const web::json::value& rawThumb)
            {
                VideoThumb::Thumbnail t;
                JsonWrapper w(rawThumb.at(name));

                t.Type = w["type"].as_string();
                t.Url = w["url"].as_string();

                return t;
            }
            VideoThumb createThumbnails(const web::json::value& rawThumb)
            {
                VideoThumb t;

                t.Small = createThumb("small", rawThumb);
                t.Large = createThumb("large", rawThumb);
                t.Medium = createThumb("medium", rawThumb);
                t.Template = createThumb("template", rawThumb);

                return t;
            }

            Video createVideo(const web::json::value& rawVideo)
            {
                Video v;
                JsonWrapper w(rawVideo);

                v.Id = w["_id"].as_string();
                v.BroadcasterId = w["broadcast_id"].as_string();
                v.BroadcastType = VideoType::fromString(w["broadcast_type"]);
                v.ChannelId = rawVideo.at("channel").at("_id").as_string();
                v.Created = w["crated_at"];
                v.Description = w["description"].as_string();
                v.DescriptionHtml = w["description_html"].as_string();
                v.Fps = createFps(rawVideo.at("fps"));
                v.Game = w["game"].as_string();
                v.Language = w["language"].as_string();
                v.Length = w["length"];
                v.Preview = createPreview(rawVideo.at("preview"));
                v.Published = w["published_at"];
                v.Resolution = createFps(rawVideo.at("resolution"));
                v.Status = w["status"].as_string();
                v.TagList = w["tag_list"].as_string();
                v.Thumbnails = createThumbnails(rawVideo.at("thumbnails"));
                v.Title = w["title"].as_string();
                v.Url = w["url"].as_string();
                v.Viewable = w["viewable"].as_string();
                v.ViewedAt = w["viewed_at"];
                v.Views = w["views"];

                return v;
            }

        }

        Channel getSelfChannel(const Api &api)
        {
            web::uri_builder builder("kraken/channel");

            auto response = api.reqOnce().get(builder.to_uri(), AuthScope::CHANNEL_READ);

            return createChannel(response);
        }

        Channel getChannel(const Api &api, const std::string &id)
        {
            web::uri_builder builder("kraken/channels");
            builder.append_path(id);

            auto response = api.reqOnce().get(builder.to_uri());

            return createChannel(response);
        }

        web::json::value buildUpdateChannelParams(const std::string &channelId,
                                                  const std::optional<std::string> &status,
                                                  const std::optional<std::string> &game,
                                                  const std::optional<int> &delay)
        {
            web::json::value channel;
            channel["channel"] = web::json::value::object();

            if(status)
            {
                channel.at("channel")["status"] = web::json::value::string(status.value());
            }

            if(game)
            {
                channel.at("channel")["game"] = web::json::value::string(game.value());
            }

            if(delay)
            {
                channel.at("channel")["delay"] = web::json::value::number(delay.value());
            }

            return channel;
        }

        Channel updateChannel(const Api &api,
                              const std::string &channelId,
                              const std::optional<std::string> &status,
                              const std::optional<std::string> &game,
                              const std::optional<int> &delay)
        {
            web::uri_builder builder("kraken/channels");
            builder.append_path(channelId);

            web::json::value channel = buildUpdateChannelParams(channelId, status, game, delay);

            if(channel.at("channel").size())
            {
                auto response = api.reqOnce().put(builder.to_uri(), AuthScope::CHANNEL_EDITOR, channel);
                return createChannel(response);
            }
            else
            {
                return getChannel(api, channelId);
            }

        }

        Channel updateChannelGame(const Api &api, const std::string &channelId, const std::string &game)
        {
            return updateChannel(api, channelId, std::nullopt, game, std::nullopt);
        }

        Channel updateChannelDelay(const Api &api, const std::string &channelId, int delay)
        {
            return updateChannel(api, channelId, std::nullopt, std::nullopt, delay);
        }

        Channel updateChannelStatus(const Api &api, const std::string &channelId, const std::string &status)
        {
            return updateChannel(api, channelId, status, std::nullopt, std::nullopt);
        }

        User createUser(const web::json::value &rawUser)
        {
            JsonWrapper w{rawUser};
            User u;
            u.Id = w["_id"];
            u.Bio = w["bio"].as_string();
            u.Created = w["created_at"];
            u.Updated = w["updated_at"];
            u.DisplayName = w["display_name"].as_string();
            u.Logo = w["logo"].as_string();
            u.Name = w["name"].as_string();
            u.Type = UserType::fromString(w["type"].as_string());

            return u;

        }

        std::vector<User> getChannelEditors(const Api &api, const std::string &channelId)
        {
            web::uri_builder builder("kraken/channels/" + channelId + "/editors");
            auto response = api.reqOnce().get(builder.to_uri(), AuthScope::CHANNEL_READ);

            std::vector<User> result;

            if(response.has_array_field("users"))
            {
                auto users = response.at("users").as_array();
                for(const auto& user: users)
                {
                    result.push_back(createUser(user));
                }
            }

            return result;
        }

        std::vector<Team> getChannelTeams(const Api &api, const std::string &channelId)
        {
            web::uri_builder builder("kraken/channels/" + channelId + "/teams");

            auto response = api.reqOnce().get(builder.to_uri());

            std::vector<Team> result;

            if(response.has_array_field("teams"))
            {
                for(auto&& rawTeam: response.at("teams").as_array())
                {
                    result.push_back(createTeam(rawTeam));
                }
            }

            return result;
        }

        std::vector<Subscription>
        getChannelSubscription(const Api &api,
                               const std::string &channelId,
                               int limit,
                               int offset,
                               Direction::Value direction)
        {
            auto response = api.reqOnce().get(getChannelSubscriptionsUri(channelId, limit, offset, direction));

            std::vector<Subscription> result;

            if(response.has_array_field("data"))
            {
                for(const auto& rawSubscription: response.at("data").as_array())
                {
                    result.push_back(createSubscription(rawSubscription));
                }
            }
            return std::vector<Subscription>();
        }

        std::tuple<unsigned long long, std::vector<v5::Video>>
        getChannelVideos(const Api &api, const std::string &channelId, const VideoOptions *opt)
        {
            return std::tuple<unsigned long long, std::vector<v5::Video>>();
        }
    }
}
