#pragma once

#include <memory>
#include "MakeRequest.h"
#include "TwitchGame.h"
#include "Logger.h"

//Twitch games collection
namespace TwitchXX
{
	extern std::shared_ptr<Logger> Log;

	class TwitchGames
	{
	public:
		// Twitch retrieves games information in chunks
		// Each chunk states total number of objects available
		// Default number of objects in chunk is 10
		TwitchGames() : TwitchGames(10) {} ;
		explicit TwitchGames(int limit);
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
		static size_t _total_size;
		TwitchGamesContainer _games;
		size_t _requested_size;
		size_t _offset;
		size_t _limit;

		static TwitchGame CreateGame(const web::json::value& value);
		TwitchGamesContainer FetchChunk(size_t limit, size_t offset);
		static void FillCollection(TwitchGame::ImageCollection& col, const web::json::value& json);
		static web::uri_builder GetBuilder(size_t limit, size_t offset);
		static void UpdateTotalGamesNumber(const web::json::value& response)
		{
			auto total = response.at(U("_total"));
			if (total.is_null() || !total.is_number()) return;
#ifdef _DEBUG
			auto new_total = total.as_integer();
			if (new_total != _total_size)
			{
				std::wstringstream s;
				s << "Total amount of games changed from " << _total_size << " to " << new_total << std::endl;
				Log->Log(s.str(), Logger::LogLevel::Debug);
			}
#endif //_DEBUG
			_total_size = new_total;
		};
	};


}

