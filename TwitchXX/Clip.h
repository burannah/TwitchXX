//
// Created by buran on 17/01/18.
//

#ifndef TWITCHXX_CLIP_H
#define TWITCHXX_CLIP_H

#include <TwitchDef.h>

namespace TwitchXX
{

    class Api;
    class ClipOptions;

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
        std::string Id;               ///< Clip id
        std::string EditUrl;          ///< Url to edit this clip
        size_t      Limit;            ///< Maximum number of Create Clip requests allowed (per minute)
        size_t      Remaining;        ///< Number of Create Clip requests remaining for current time interval
    };

    /**
    *****************************************************************************************
    *  @brief      Create a new clip and get its id and URL for editing.
    *  @details    To create a clip - call this function with broadcaster id. Broadcaster should
    *              be live, or you'll get 404 error back
    *  @param      api - API object  providing request and auth objects
    *  @param      broadcaster - broadcaster id (NOT CHANNEL NAME) - if wrong id provided will
    *              return 503 error back.
    *  @return     Handle structure with populated Id and EditUrl fields.
    ****************************************************************************************/
    static Handle CreateAndGetHandle(const Api &api, unsigned long long int broadcaster);

    /**
    *****************************************************************************************
    *  @brief      Create an instance of TwitchXX::Clip class - representing some clip.
    *  @details    To get a clip info just call the constructor with id value. If id is wrong
    *              you'll get 404 error back
    *  @param      api - API object which contains auth tokens and request objects
    *  @param      id - clip id - usually five random words
    ****************************************************************************************/
    explicit Clip(const Api &api, const std::string &id);
    explicit Clip() = default;

    //@{
    /** Clip properties. */
    std::string        Id;

    std::string        Url;

    std::string        EmbedUrl;

    unsigned long long BroadcasterId{};

    unsigned long long CreatorId{};

    unsigned long long VideoId{};

    unsigned long long GameId{};

    std::string        Language;

    std::string        Title;

    unsigned int       ViewCount{};

    Date               Created;

    std::string        Thumb;
    //@}

    ///Compare two Clip objects
    bool operator==(const Clip& other) const;
};

    /**
    *****************************************************************************************
    *  @brief      Request a number of clips.
    *  @details    Get a number (up to 100) of clips by providing a parameters object.
    *  @param      api - API object  providing request and auth objects
    *  @param      params - request parameters
    *  @return     a vector of TwitchXX::Clip objects (if any were found).
    ****************************************************************************************/
    std::tuple<std::vector<Clip>, std::string> getClips(const Api &api, const ClipOptions& params);
}



#endif //TWITCHXX_CLIP_H
