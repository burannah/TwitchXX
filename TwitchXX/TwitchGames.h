#pragma once

#include <memory>
#include "MakeRequest.h"
#include "TwitchGame.h"

//Twitch games collection
namespace TwitchXX
{
	class TwitchGames
	{
	public:
		// Twitch retrieves games information in chunks
		// Each chunk states total number of objects available
		// Default number of objects in chunk is 10
		TwitchGames() : TwitchGames(10) {} ;
		explicit TwitchGames(int limit);
		virtual ~TwitchGames();

		const TwitchGamesContainer& Games() const { return _games; };
		const TwitchGamesContainer& Games(bool fetch_all = false)
		{
			if(fetch_all)
			{
				FetchAllGames();
			}
			return _games;
		}

		void FetchAllGames();
		void FetchGames();
		void FetchGames(size_t limit);

	private:
		TwitchGamesContainer _games;
		size_t _size;
		size_t _offset;
		size_t _limit;

		void FetchChunk(size_t limit, size_t offset);
		static void FillCollection(TwitchGame::ImageCollection& col, const web::json::value& json);
		static TwitchGame CreateGame(const web::json::value& value);
	};


}

