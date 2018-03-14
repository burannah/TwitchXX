//
// Created by buran on 05/03/18.
//

#ifndef TWITCHXX_USER_H
#define TWITCHXX_USER_H

#include <string>
#include <Property.h>
#include <UserType.h>
#include <BroadcasterType.h>

namespace TwitchXX
{
    class Api;

    ///User description class
    class User
    {
    public:
        std::string            Id;                //< User id
        std::string            Login;             //< User login
        std::string            DisplayName;       //< Display name
        UserType::Value        Type;              //< User type (see UserType)
        BroadcasterType::Value BroadcaterType;    //< Broadcaster type (see BroadcasterType)
        std::string            Description;       //< User's channel description
        std::string            AvatarUrl;         //< URL to the user's profile image
        std::string            OfflineImageUrl;   //< URL to the user's offline image
        long long unsigned     ViewCount;         //< Total number of views of the user's channel
        std::string            Email;             //< User’s email address. Returned if the request includes
                                                  //< the user:read:edit scope.

    };

    /***
    * Fetch single user by id or login. Either id or login should be specified.
    * @param id - use id (optional)
    * @param login - user login (optional)
    * @return User object
    */
    User getUser(std::string id, std::string login = std::string{});

    /***
    * Fetch a number of users specified by ids and or logins.
    * Both parameters are optional (can be empty), but at least one should be specified.
    * @param ids - array of user ids to fetch (Maximum: 100)
    * @param logins - array of user logins to fetch (Maximum: 100)
    * @return a tuple with vector of Strem objects and a cursor
    * @throw TwitchXX::TwitchException if ids or logins size is > 100 or both empty;
    */
    std::vector<User> getUsers(std::vector<std::string> ids, std::vector<std::string> logins);

    /***
    * Update user's description. The user is specified by user access token provided by Api object
    * @param api - a general Twitch Api object with all required tokens and request object
    * @param newDescription - new description text
    * @return updated User object
    * @throw TwitchXX::TwitchException if something went wrong
    */
    User updateUserDescription(const Api& api, const std::string& newDescription);
}



#endif //TWITCHXX_USER_H
