//
// Created by buran on 23/02/18.
//

#ifndef TWITCHXX_STREAM_H
#define TWITCHXX_STREAM_H

#include <string>
#include <Property.h>

namespace TwitchXX
{

    /***
    * Stream descriptor
    */
    class Stream
    {
    public:
        Property<std::string>              Id;
        Property<std::string>              UserId;
        Property<std::string>              GameId;
        Property<std::vector<std::string>> CommunityIds;
        Property<std::string>              Title;
        Property<StreamType::Value>        Type;
        Property<unsigned long long>       Viewers;
        Property<Date>                     Started;
        Property<std::string>              Language;
        Property<std::string>              Thumb;
    };

    /***
    * Fetch Stream objects. Forward-only request
    * @param count - count of objects per batch (Maximum: 100)
    * @param cursor - forward ('after') cursor. Optional
    * @return a tuple with vector of Strem objects and a cursor
    * @throw TwitchXX::TwitchException in case of count is > 100;
    */
    std::tuple<std::vector<Stream>, std::string> getStreams(size_t count, const char *cursor = nullptr);

    /***
    * Fetch Stream objects. More complex way of request.
    * @param opt - request options. See GetStreamsOptions for details.
    * @return a tuple with vector of Stream objects and a cursor
    * @throw TwitchXX::TwitchException in case some of the parameters are incorrect.
    */
    std::tuple<std::vector<Stream>, std::string> getStreams(const GetStreamsOptions& opt);
}


#endif //TWITCHXX_STREAM_H
