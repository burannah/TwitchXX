//
// Created by buran on 30/06/18.
//

#include "TestUtils.h"
#include <TestConstants.h>
#include <Utility.h>

TwitchXX::options& TestUtils::initOptionsFromConfig(const std::string &path)
{
    auto & opt = getOptions();

    utility::ifstream_t options_file(!path.empty() ?  path.c_str() : "twitchxx.cfg");
    utility::string_t line;
    while(std::getline(options_file,line))
    {
        utility::stringstream_t iss(line);
        utility::string_t name, value;
        std::getline(iss, name, '=');
        std::getline(iss, value);
        if(name[0] == '#')
        {
            //Skip comments
            continue;
        }
        TwitchXX::trim(name);
        TwitchXX::trim(value);
        opt.insert({name, value});
    }

    return opt;

}

TwitchXX::options &TestUtils::initOptionsFromConfigV5(const std::string &path)
{
    auto& opt  =  initOptionsFromConfig(path);
    opt["version"] = v5;
    return opt;
}

