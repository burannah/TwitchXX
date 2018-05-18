//
// Created by buran on 19/05/18.
//

#ifndef TWITCHXX_CLIPOPTIONS_H
#define TWITCHXX_CLIPOPTIONS_H

#include <string>
#include <vector>

namespace TwitchXX
{
    /// Request options for TwitchXX::getClips request
    struct ClipOptions
    {
        ///@{ Required parameters
        /// For a query to be valid, id (one or more), broadcaster_id, or game_id must be specified.
        /// You may specify only one of these parameters.
        unsigned long long broadcasterId = 0;       ///< Broadcaster Id
        unsigned long long gameId = 0;              ///< Game Id
        std::vector<std::string> ids;           ///< IDs of the clip being queried. Limit: 100.
        ///@}

        ///@{ Optional parameters
        std::string              after;         ///< Forward cursor
        std::string              before;        ///< Backward cursor
        int                      first = 20;    ///< Maximum number of objects to return.
                                                ///< Maximum: 100. Default: 20.
        ///@}

    };
}

#endif //TWITCHXX_CLIPOPTIONS_H
