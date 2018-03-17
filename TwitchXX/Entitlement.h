//
// Created by buran on 23/01/18.
//

#ifndef TWITCHXX_ENTITLEMENT_H
#define TWITCHXX_ENTITLEMENT_H

#include <string>

namespace TwitchXX
{
    /***
     * Creates a URL where you can upload a manifest file and notify users that they have an entitlement.
     * Entitlements are digital items that users are entitled to use.
     * Twitch entitlements are granted to users gratis or as part of a purchase on Twitch.
     * See the <a href="https://dev.twitch.tv/docs/drops">Drops Guide</a> for details about using this endpoint to notify users about Drops.
     */
    class Entitlement
    {
    public:
        enum class Type
        {
            bulk_drops_grant
        };

        static std::string getEntitlementTypeString(Type t);

        explicit Entitlement(const std::string& id, Type t = Type::bulk_drops_grant);

        std::string Url;
        std::string Id;
        Type        EntitlementType;

    };

}



#endif //TWITCHXX_ENTITLEMENT_H
