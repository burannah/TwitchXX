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
        namespace
        {
            Channel createChannel(const web::json::value &raw)
            {
                Channel c;

                if(raw.has_field("name") && raw.at("name").is_string())
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
    }
}
