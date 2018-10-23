//
// Created by buran on 10/23/18.
//

#ifndef TWITCHXX_UTILSINTERNAL_H
#define TWITCHXX_UTILSINTERNAL_H


#include <string>
#include <cpprest/json.h>

class UtilsInternal
{
public:
    static std::string getCursor(const web::json::value& response);

};


#endif //TWITCHXX_UTILSINTERNAL_H
