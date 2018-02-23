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
     * Stream type enum & helpers
     */
    struct StreamType
    {
        /***
         * Stream types
         */
        enum class Value
        {
            ALL,
            LIVE,
            VODCAST,
        };

        /// Stream type enum value to string
        static std::string toString(StreamType::Value v);

        /// Stream type enum value from string
        static StreamType::Value  fromString(const std::string s);

        /// Stream type enum value from int
        static StreamType::Value fromInt(int i);
    };

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
     * Get Streams request parameter structure;
     */
    struct GetStreamsOptions
    {
        std::string after;  ///< Cursor for forward pagination: tells the server where to start fetching
                            ///< the next set of results, in a multi-page response.
        std::string before; ///< Cursor for backward pagination: tells the server where to start fetching
                            ///< the next set of results, in a multi-page response.
        std::vector<std::string> communitIds; ///< Returns streams in a specified community ID.
                                             ///< You can specify up to 100 IDs.
        size_t first; ///< Maximum number of objects to return. Maximum: 100. Default: 20.

        std::vector<std::string> gameIds; ///< Returns streams broadcasting a specified game ID.
                                         ///< You can specify up to 100 IDs.
        std::vector<std::string> langs; ///< Returns streams broadcasting a specified game ID.
                                       ///< You can specify up to 100 IDs.
        StreamType::Value type; ///< Stream type: "all", "live", "vodcast". Default: "all".

        std::vector<std::string> userIds; ///< Returns streams broadcast by one or more specified
                                          ///< user IDs. You can specify up to 100 IDs.
        std::vector<std::string> userLogin; ///< Returns streams broadcast by one or more specified
                                            ///< user login names. You can specify up to 100 names.
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
