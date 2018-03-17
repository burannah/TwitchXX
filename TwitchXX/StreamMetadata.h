//
// Created by buran on 03/03/18.
//

#ifndef TWITCHXX_STREAMMETADATA_H
#define TWITCHXX_STREAMMETADATA_H

#include <string>
#include <Property.h>
#include <StreamsOptions.h>
#include "Api.h"

namespace TwitchXX
{
    /// Overwatch stream metadata
    struct Overwatch
    {
        std::string Role;     ///< Broadcaster's current Role
        std::string Name;     ///< Broadcaster's name
        std::string Ability;  ///< Broadcaster's ability
    };

    ///Hearthstone stream metadata
    struct Hearthstone
    {
        ///Player's metadata
        struct Hero
        {
            std::string Type;     ///< Type
            std::string Class;    ///< Class
            std::string Name;     ///< Name
        };

        Hero Broadcaster;                   ///< Broadcaster's hero metadata
        Hero Opponent;                      ///< Opponent's hero metadata
    };

    ///Stream metadata class
    class StreamMetadata
    {
    public:
        ///Rate limits for stream metadata request
        struct RateLimits
        {
            int Remaining;      ///< Number of remaining request till the end of current time interval (see RequestLimits)
            int Limit;          ///< Maximum number of stream metadata requests per time interval (see RequestLimits)
        };

        StreamMetadata() = default;

        StreamMetadata(const StreamMetadata& other)
        {
            UserId = other.UserId;
            GameId = other.GameId;

            if(other.overwatch)
            {
                overwatch = std::make_unique<Overwatch>(*other.overwatch);
            }
            else if(other.hearthstone)
            {
                hearthstone = std::make_unique<Hearthstone>(*other.hearthstone);
            }
        }


        unsigned long long UserId;   ///< User id
        unsigned long long GameId;   ///< Game id (at the moment can be 488552 (Overwatch), 138585 (Hearthstone), or null)


        std::unique_ptr<Overwatch> overwatch;            ///< Overwatch stream metadata
        std::unique_ptr<Hearthstone> hearthstone;        ///< Hearthstone stream metadata
    };

    /***
    * Fetch Stream metadata objects. Forward-only request
    * @param api - api objects containing request and auth objects
    * @param count - count of objects per batch (Maximum: 100)
    * @param cursor - forward ('after') cursor. Optional
    * @return a tuple with vector of Strem objects and a cursor
    * @throw TwitchXX::TwitchException in case of count is > 100;
    */
    std::tuple<std::vector<TwitchXX::StreamMetadata>, std::string>
    getStreamsMetadata(const Api& api,
                       size_t count,
                       StreamMetadata::RateLimits* limits = nullptr,
                       const char *cursor = nullptr);

    /***
    * Fetch Stream metadata objects. More complex way of request.
    * @param api - api objects containing request and auth objects
    * @param opt - request options. See GetStreamsOptions for details.
    * @return a tuple with vector of Stream objects and a cursor
    * @throw TwitchXX::TwitchException in case some of the parameters are incorrect.
    */
    std::tuple<std::vector<StreamMetadata>, std::string>
    getStreamsMetadata(const Api& api,
                       const StreamsOptions& opt,
                       StreamMetadata::RateLimits* limits = nullptr);
}


#endif //TWITCHXX_STREAMMETADATA_H
