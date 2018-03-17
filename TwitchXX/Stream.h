//
// Created by buran on 23/02/18.
//

#ifndef TWITCHXX_STREAM_H
#define TWITCHXX_STREAM_H

#include <string>
#include <Property.h>
#include <StreamType.h>
#include <StreamsOptions.h>

namespace TwitchXX
{

    /***
    * Stream descriptor
    */
    class Stream
    {
    public:
        unsigned long long       Id;
        unsigned long long       UserId;
        unsigned long long       GameId;
        std::vector<std::string> CommunityIds;
        std::string              Title;
        StreamType::Value        Type;
        unsigned long long       Viewers;
        Date                     Started;
        std::string              Language;
        std::string              Thumb;
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
    std::tuple<std::vector<Stream>, std::string> getStreams(const StreamsOptions& opt);
}


#endif //TWITCHXX_STREAM_H
