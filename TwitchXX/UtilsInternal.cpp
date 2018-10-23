//
// Created by buran on 10/23/18.
//

#include "UtilsInternal.h"

std::string UtilsInternal::getCursor(const web::json::value &response)
{
    std::string new_cursor;
    try
    {
        new_cursor = response.at("pagination").at("cursor").as_string();
    }
    catch(web::json::json_exception& e)
    {
        new_cursor = "Error cursor!";
    }

    return new_cursor;
}
