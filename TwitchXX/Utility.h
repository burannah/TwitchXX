//
// Created by buran on 21/01/18.
//

#ifndef TWITCHXX_UTILITY_H
#define TWITCHXX_UTILITY_H

#include <TwitchDef.h>

namespace TwitchXX
{
	extern void trim(utility::string_t& s);

	///Date from string
	///@param cs string represetnaion of ISO 8601 format time
	///@return Date value
	Date DateFromString(const utility::string_t& cs);

    ///Date to string
    ///@param tp Date object
    ///@return date string in ISO 8601 format
    utility::string_t DateToString(const Date& tp);
}

#endif //TWITCHXX_UTILITY_H
