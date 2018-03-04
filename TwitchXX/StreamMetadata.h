//
// Created by buran on 03/03/18.
//

#ifndef TWITCHXX_STREAMMETADATA_H
#define TWITCHXX_STREAMMETADATA_H

#include <string>
#include <Property.h>
#include <StreamsOptions.h>

namespace TwitchXX
{
    /// Overwatch stream metadata
    struct Overwatch
    {
        Property<std::string> Role;     ///< Broadcaster's current Role
        Property<std::string> Name;     ///< Broadcaster's name
        Property<std::string> Ability;  ///< Broadcaster's ability
    };

    ///Hearthstone stream metadata
    struct Hearthstone
    {
        ///Player's metadata
        struct Hero
        {
            Property<std::string> Type;     ///< Type
            Property<std::string> Class;    ///< Class
            Property<std::string> Name;     ///< Name
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

        Property<std::string> UserId;   ///< User id
        Property<std::string> GameId;   ///< Game id (at the moment can be 488552 (Overwatch), 138585 (Hearthstone), or null)


        //TODO: Should be nullable objects
        Overwatch overwatch;            ///< Overwatch stream metadata
        Hearthstone hearthstone;        ///< Hearthstone stream metadata
    };

    /***
    * Fetch Stream metadata objects. Forward-only request
    * @param count - count of objects per batch (Maximum: 100)
    * @param cursor - forward ('after') cursor. Optional
    * @return a tuple with vector of Strem objects and a cursor
    * @throw TwitchXX::TwitchException in case of count is > 100;
    */
    std::tuple<std::vector<TwitchXX::StreamMetadata>, std::string>
    getStreamsMetadata(size_t count,
                       StreamMetadata::RateLimits* limits = nullptr,
                       const char *cursor = nullptr);

    /***
    * Fetch Stream metadata objects. More complex way of request.
    * @param opt - request options. See GetStreamsOptions for details.
    * @return a tuple with vector of Stream objects and a cursor
    * @throw TwitchXX::TwitchException in case some of the parameters are incorrect.
    */
    std::tuple<std::vector<StreamMetadata>, std::string>
    getStreamsMetadata(const StreamsOptions& opt,
                       StreamMetadata::RateLimits* limits = nullptr);
}


#endif //TWITCHXX_STREAMMETADATA_H
