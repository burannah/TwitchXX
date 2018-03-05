//
// Created by buran on 05/03/18.
//

#ifndef TWITCHXX_USER_H
#define TWITCHXX_USER_H

#include <string>
#include <Property.h>
#include <UserType.h>
#include "BroadcasterType.h"

namespace TwitchXX
{
    ///User description class
    class User
    {
    public:
        Property<std::string> Id;                           //< User id
        Property<std::string> Login;                        //< User login
        Property<std::string> DisplayName;                  //< Display name
        Property<UserType::Value> Type;                     //< User type (see UserType)
        Property<BroadcasterType::Value> BroadcaterType;    //< Broadcaster type (see BroadcasterType)
        Property<std::string> Description;                  //< User's channel description
        Property<std::string> AvatarUrl;                    //< URL to the user's profile image
        Property<std::string> OfflineImageUrl;              //< URL to the user's offline image
        Property<long long> ViewCount;                      //< Total number of views of the user's channel
        Property<std::string> Email;                        //< User’s email address. Returned if the request includes
                                                            // the user:read:edit scope.

    };
}



#endif //TWITCHXX_USER_H
