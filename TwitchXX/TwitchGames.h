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
	class TwitchGames : public TwitchRequest<TwitchGame>
	{
	public:
		///Constructor
		///@param request transport object
		///@param limit number of game objects per request. Twitch retrieves games information in chunks. Each chunk states total number of objects available
		///				Default number of objects in chunk is 10.
		explicit TwitchGames(std::shared_ptr<MakeRequest> request, int limit = 10) 
			: TwitchRequest<TwitchGame>(request,limit) 
		{ 
		};

		///Get n top games
		///@param n max number of games to fetch (by number of viewers). If n == 0 all games will be fetched. The final amount of games retrieved can be less 
		///			than total number indicated in response due to some cahcing stuff (hope Twitch will fix it some day).
		TwitchGamesVector GetTopGames(size_t n = 0);


		///Get total number of games being broadcasted on Twitch at the moment
		///Performs additional request to get first (top most) game, to retrieve total number at the moment.
		size_t GetTotalNumber()
		{
			FetchChunk(GetBuilder(1, 0).to_uri(),U("top")); return _total_size;
		};

		///Get chunk of games objects
		///@param offset offset position in games top list
		///@param limit number of games to request (maximum 100)
		TwitchGamesContainer GetChunk(size_t offset, size_t limit)
		{
			GetTotalNumber();
			if(offset < 0 || offset > _total_size)
			{
				std::invalid_argument("Offset must be in [0;Total Games) ");
			}
			if(limit < 1 || limit > 100 )
			{
				std::invalid_argument("Limit must be in [1:100]");
			}

			return FetchChunk(GetBuilder(limit,offset).to_uri(), U("top"));
		};

	private:
		web::uri_builder GetBuilder(size_t limit, size_t offset) const;
	};


	ImageCollection CreateCollection(const web::json::value& json); ///< Create image collection from json for TwitchGame object
	template<>
	TwitchGame Create(const web::json::value& json); ///< Create TwitchGame object from json
}

