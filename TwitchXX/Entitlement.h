//
// Created by buran on 23/01/18.
//

#ifndef TWITCHXX_ENTITLEMENT_H
#define TWITCHXX_ENTITLEMENT_H

#include <string>

namespace TwitchXX
{
    class Api;
    /**
     * Creates a URL where you can upload a manifest file and notify users that they have an entitlement.
     * Entitlements are digital items that users are entitled to use.
     * Twitch entitlements are granted to users gratis or as part of a purchase on Twitch.
     * See the <a href="https://dev.twitch.tv/docs/drops">Drops Guide</a> for details about using this endpoint to notify users about Drops.
     */
    class Entitlement
    {
    public:
        /// Entitlement type enum (only one value present at the moment
        enum class Type
        {
            bulk_drops_grant
        };

        /// Convert entitlement type enum value to string
        static std::string getEntitlementTypeString(Type t);

        /// Constructor
        explicit Entitlement(const Api &api, const std::string &id, TwitchXX::Entitlement::Type t);

        std::string Url;             ///< Entitlement URL
        std::string Id;              ///< Id
        Type        EntitlementType; ///< Type

    };

}



#endif //TWITCHXX_ENTITLEMENT_H
