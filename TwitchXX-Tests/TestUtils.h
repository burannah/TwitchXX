//
// Created by buran on 30/06/18.
//

#ifndef TWITCHXX_TESTUTILS_H
#define TWITCHXX_TESTUTILS_H


#include <TwitchDef.h>

class TestUtils
{
public:
    ///Global request parameters holder
    static TwitchXX::options& getOptions()
    {
        static TwitchXX::options opt;
        return opt;
    }

    ///Init request options by default config
    static TwitchXX::options& initOptionsFromConfig(const std::string& path = std::string());

    ///Init request options by default config and set version to v5
    static TwitchXX::options& initOptionsFromConfigV5(const std::string& path = std::string());

};


#endif //TWITCHXX_TESTUTILS_H
