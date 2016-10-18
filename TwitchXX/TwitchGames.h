#pragma once

#include <memory>
#include "MakeRequest.h"
#include "TwitchGame.h"
#include "Logger.h"
#include "TwitchRequest.h"

///Twitch games collection
namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;
	///Twitch gamess request class
	/** This class encapsulates all requests that are related to twitch games operations (request top games basically)*/
	class TwitchGames : public TwitchRequest
	{
	public:
		///Constructor
		///@param equest transport object
		explicit TwitchGames(MakeRequest equest)
			: TwitchRequest(equest)
		{ 
		};

		///Get n top games
		///@param n max number of games to fetch (by number of viewers). If n == 0 all games will be fetched. The final amount of games retrieved can be less 
		///			than total number indicated in response due to some cahcing stuff (hope Twitch will fix it some day).
		TwitchGamesContainer GetTopGames(size_t n = 0) const;


		///Update total number of games being broadcasted on Twitch at the moment
		///Performs additional request to get first (top most) game, to retrieve total number at the moment.
		///@return  new total
		size_t UpdateTotal() const;
	};


	ImageCollection CreateCollection(const web::json::value& json); ///< Create image collection from json for TwitchGame object
	template<>
	TwitchGame Create(const web::json::value& json); ///< Create TwitchGame object from json
}

