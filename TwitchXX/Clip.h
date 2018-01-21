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
        utility::string_t Id;               ///< Clip id
        utility::string_t EditUrl;          ///< Url to edit this clip
        size_t            Limit;            ///< Maximum number of Create Clip requests allowed (per minute)
        size_t            Remaining;        ///< Number of Create Clip requests remaining for current time interval
    };

    /**
    *****************************************************************************************
    *  @brief      Create a new clip and get its id and URL for editing.
    *  @details    To create a clip - call this function with broadcaster id. Broadcaster should
    *              be live, or you'll get 404 error back
    *  @param      broadcaster - broadcaster id (NOT CHANNEL NAME) - if wrong id provided will
    *              return 503 error back.
    *  @return     Handle structure with populated Id and EditUrl fields.
    ****************************************************************************************/
    static Handle CreateAndGetHandle(const utility::string_t &broadcaster);

    /**
    *****************************************************************************************
    *  @brief      Create an instance of TwitchXX::Clip class - representing some clip.
    *  @details    To get a clip info just call the constructor with id value. If id is wrong
    *              you'll get 404 error back
    *  @param      id - clip id - usually five random words
    ****************************************************************************************/
    explicit Clip (const utility::string_t& id);

    //@{
    /** Clip properties. */
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
    //@}
};

}



#endif //TWITCHXX_CLIP_H
