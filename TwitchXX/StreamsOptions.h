//
// Created by buran on 03/03/18.
//

#ifndef TWITCHXX_STREAMSOPTIONS_H
#define TWITCHXX_STREAMSOPTIONS_H

#include <string>
#include <StreamType.h>
#include <vector>

namespace web
{
    class uri_builder;
}

/***
 * Get Streams request parameter structure;
 */
namespace TwitchXX
{
    /// Class to descrube getStreams request options
    struct StreamsOptions
    {
        std::string after;  ///< Cursor for forward pagination: tells the server where to start fetching
        ///< the next set of results, in a multi-page response.
        std::string before; ///< Cursor for backward pagination: tells the server where to start fetching
        ///< the next set of results, in a multi-page response.
        std::vector<std::string> communitIds; ///< Returns streams in a specified community ID.
        ///< You can specify up to 100 IDs.
        unsigned long first; ///< Maximum number of objects to return. Maximum: 100. Default: 20.

        std::vector<unsigned long long> gameIds; ///< Returns streams broadcasting a specified game ID.
        ///< You can specify up to 100 IDs.
        std::vector<std::string> langs; ///< Returns streams broadcasting a specified game ID.
        ///< You can specify up to 100 IDs.
        StreamType::Value type; ///< Stream type: "all", "live", "vodcast". Default: "all".

        std::vector<unsigned long long> userIds; ///< Returns streams broadcast by one or more specified
        ///< user IDs. You can specify up to 100 IDs.
        std::vector<std::string> userLogin; ///< Returns streams broadcast by one or more specified
        ///< user login names. You can specify up to 100 names.

        ///Validate StreamOptions object
        static void validate(const StreamsOptions& opt);

        ///Fill uri_builder with options values
        static void fillBuilder(web::uri_builder& builder, const StreamsOptions& opt);

    };
}
#endif //TWITCHXX_STREAMSOPTIONS_H
