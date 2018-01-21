//
// Created by buran on 21/01/18.
//

#ifndef TWITCHXX_UTILITY_H
#define TWITCHXX_UTILITY_H

namespace TwitchXX
{
	extern void trim(utility::string_t& s);
	Date DateFromString(const utility::string_t& cs);
    utility::string_t DateToString(const Date& tp);
}

#endif //TWITCHXX_UTILITY_H
