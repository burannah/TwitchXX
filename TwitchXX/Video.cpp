//
// Created by buran on 14/03/18.
//

#include <Video.h>
#include <VideoOptions.h>
#include <Api.h>
#include <TwitchException.h>

std::tuple<std::vector<TwitchXX::Video>, std::string>
TwitchXX::getVideos(const Api &api, const std::vector<u_int64_t> *ids, const u_int64_t *userId,
                    const u_int64_t *gameId, const VideoOptions *opt)
{
    if(ids && ids->size() > 100)
    {
        throw TwitchException("Too many video ids");
    }

    web::uri_builder builder("helix/videos");

    if(ids)
    {
        addRangeOfParamsToBuilder(builder, "id", *ids);
    }
    else if(userId)
    {
        builder.append_query("user_id", *userId);
    }
    else if(gameId)
    {
        builder.append_query("game_id", *gameId);
    }
    else
    {
        //TODO: Can there be two or three? Can there be nonel
        throw TwitchException("Video id(s), user id or game id should be specified");
    }

    if(userId)
    {

    }

    return std::tuple<std::vector<TwitchXX::Video>, std::string>();
}
