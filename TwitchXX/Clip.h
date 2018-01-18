//
// Created by buran on 17/01/18.
//

#ifndef TWITCHXX_CLIP_H
#define TWITCHXX_CLIP_H

#include <cpprest/details/basic_types.h>
#include "Property.h"

namespace TwitchXX
{

///Create and access existing clip object
/** This class encapsulates two Twitch API requests:
 * Create clip: https://dev.twitch.tv/docs/api/reference#create-clip
 * Get clip: https://dev.twitch.tv/docs/api/reference#get-clip
 * */
class Clip
{
public:

    ///Simple structure to reference a clip
    struct Handle
    {
        utility::string_t Id;
        utility::string_t EditUrl;
        size_t            Limit;
        size_t            Remaining;
    };

    ///Get a link to the clip editing page
    static Handle CreateAndGetHandle(const utility::string_t &broadcaster);

    explicit Clip (const utility::string_t& id);

    Property<utility::string_t> Id;

    Property<utility::string_t> Url;

    Property<utility::string_t> EmbedUrl;

    Property<utility::string_t> BroadcasterId;

    Property<utility::string_t> CreatorId;

    Property<utility::string_t> VideoId;

    Property<utility::string_t> GameId;

    Property<utility::string_t> Language;

    Property<utility::string_t> Title;

    Property<unsigned int>      ViewCount;

    Property<Date>              Created;

    Property<utility::string_t> Thumb;
};

}



#endif //TWITCHXX_CLIP_H
