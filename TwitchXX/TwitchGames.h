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

		};
		virtual ~TwitchGames();

		TwitchGamesContainer GetTopGames(size_t n = 0);


		size_t GetTotalNumber() { FetchChunk(0, 1); return _total_size; };
		TwitchGamesContainer GetChunk(size_t offset, size_t limit)
		{
			FetchChunk(0, 1); 
			if(offset < 0 || offset > _total_size)
			{
				std::invalid_argument("Offset must be in [0;Total Games) ");
			}
			if(limit < 1 || limit > 100 )
			{
				std::invalid_argument("Limit must be in [1:100]");
			}

			return FetchChunk(limit, offset);
		};


	private:
		web::uri_builder GetBuilder(size_t limit, size_t offset) override;
	};


	TwitchGame Create(const web::json::value obj);
	void FillCollection(TwitchGame::ImageCollection& col, const web::json::value& json);

}

