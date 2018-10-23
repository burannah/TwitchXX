//
// Created by buran on 09/07/18.
//

#include <JsonWrapper.h>
#include <BroadcasterType.h>
#include "Channel.h"

namespace TwitchXX
{
    namespace v5
    {
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
    }
}
