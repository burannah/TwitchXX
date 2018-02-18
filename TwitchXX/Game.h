//
// Created by buran on 29/01/18.
//

#ifndef TWITCHXX_GAME_H
#define TWITCHXX_GAME_H

#include <string>
#include <Property.h>

namespace TwitchXX
{
    /***
    * Gets game information by game ID or name.
    */
    class Game
    {

    public:
        //TODO:
        //2. Method to get top games
        /***
         * Fetch game information from Twitch. Either id or name should be present
         * @param id - Twitch game id
         * @param name - Name
         */
        explicit Game(const std::string& id, const std::string& name = "");

        /***
         * Simple constructor to just create a game object. Checks that id and name paramaters
         * are not empty
         * @param id - Twitch game id (required)
         * @param name - Game name (required)
         * @param url - Box Art image url (optional)
         */
        explicit Game(const std::string& id, const std::string& name, const std::string& url);

        Property<std::string> Id;       //< Twitch game Id
        Property<std::string> Name;     //< Game title
        Property<std::string> BoxArt;   //< Url template for box art image
    };

    /***
     * Method to get Game objects by ids and/or name
     * @param ids - Ids array (100 elements max)
     * @param names - Game names array (100 element max)
     * @return vector of Game objects
     */
    std::vector<Game> getGames(const std::vector<std::string>& ids, const std::vector<std::string>& names = {});
}



#endif //TWITCHXX_GAME_H
