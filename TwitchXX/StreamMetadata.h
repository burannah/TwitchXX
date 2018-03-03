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
    struct Overwatch;
    struct Harthstone;

    class StreamMetadata
    {
    public:
        Property<std::string> UserId;
        Property<std::string> GameId;

        std::unique_ptr<Overwatch> Overwatch;
        std::unique_ptr<Harthstone> Harthstone;
    };

    struct Overwatch
    {
        Property<std::string> Role;
        Property<std::string> Name;
        Property<std::string> Ability;
    };
    struct Harthstone
    {
        struct Hero
        {
            Property<std::string> Type;
            Property<std::string> Class;
            Property<std::string> Name;
        };

        Hero Broadcaster;
        Hero Opponent;
    };

    /***
    * Fetch Stream metadata objects. Forward-only request
    * @param count - count of objects per batch (Maximum: 100)
    * @param cursor - forward ('after') cursor. Optional
    * @return a tuple with vector of Strem objects and a cursor
    * @throw TwitchXX::TwitchException in case of count is > 100;
    */
    std::tuple<std::vector<TwitchXX::StreamMetadata>, std::string> getStreamsMetadata(size_t count, const char *cursor = nullptr);

    /***
    * Fetch Stream metadata objects. More complex way of request.
    * @param opt - request options. See GetStreamsOptions for details.
    * @return a tuple with vector of Stream objects and a cursor
    * @throw TwitchXX::TwitchException in case some of the parameters are incorrect.
    */
    std::tuple<std::vector<StreamMetadata>, std::string> getStreamsMetadata(const StreamsOptions& opt);
}


#endif //TWITCHXX_STREAMMETADATA_H
