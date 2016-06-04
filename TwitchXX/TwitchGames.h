#pragma once

#include <memory>
#include "MakeRequest.h"
#include "TwitchGame.h"
#include "Logger.h"
#include "TwitchRequest.h"

//Twitch games collection
namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;

	class TwitchGames : public TwitchRequest<TwitchGame>
	{
	public:
		// Twitch retrieves games information in chunks
		// Each chunk states total number of objects available
		// Default number of objects in chunk is 10
		explicit TwitchGames(int limit = 10) : TwitchRequest<TwitchGame>(limit) 
		{ 
			_root_node = U("top");
		};
		virtual ~TwitchGames();

		TwitchGamesVector GetTopGames(size_t n = 0);


		size_t GetTotalNumber()
		{
			FetchChunk(GetBuilder(1, 0).to_uri()); return _total_size;
		};
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

			return FetchChunk(GetBuilder(limit,offset).to_uri());
		};

	private:
		web::uri_builder GetBuilder(size_t limit, size_t offset);
	};


	ImageCollection CreateCollection(const web::json::value& json);
	template<>
	TwitchGame Create(const web::json::value& json);
}

