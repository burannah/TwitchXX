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
        //1. Method to get an array of games by ids
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
}



#endif //TWITCHXX_GAME_H
