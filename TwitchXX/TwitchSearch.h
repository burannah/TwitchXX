#pragma once
#include "TwitchRequest.h"
#include "TwitchException.h"
#include "TwitchGames.h"
#include "TwitchChannels.h"
#include "TwitchStreams.h"

namespace TwitchXX
{

	///Search requests agregator class
	class TwitchSearch : TwitchRequest
	{
	public:
		explicit TwitchSearch(MakeRequest request)
					: TwitchRequest(request) 
		{
		};


		///Search for specific channels
		TwitchChannelsContainer SearchChannels(const utility::string_t& query, unsigned int limit = 25, unsigned int offset = 0);

		///Search for specific streams
		TwitchStreamsContainer SearchStreams(const utility::string_t& query, unsigned int limit = 25, unsigned int offset = 0);

		///Search for specific games
		TwitchGamesContainer SearchGames(const utility::string_t& query, unsigned int limit = 25, unsigned int offset = 0);

	private:

		///The actual search subroutine
		template<typename T>
		TwitchContainer<T> Search(web::uri_builder& builder);

	
	};

	template <typename T>
	TwitchContainer<T> TwitchSearch::Search(web::uri_builder& builder)
	{
		try
		{
			auto results_node = builder.path();
			auto delimetr = results_node.find_last_of('/');
			if( delimetr != results_node.npos)
			{
				results_node = results_node.substr(delimetr + 1);
			}
			auto response = _request.get(builder.to_uri());
			if(!response.has_field(results_node) || !response.at(results_node).is_array())
			{
				throw TwitchException("Unknwon format!", _request.status_code());
			}

			TwitchContainer<T> result;

			for (const auto& element : response.at(results_node).as_array())
			{
				result.insert(Create<T>(element));
			}

			return result;
		}
		catch(TwitchException& e)
		{
			if(e.code() == web::http::status_codes::ServiceUnavailable)
			{
				throw TwitchException("Unable to retrieve search results", e.code());
			}
		}
		return {};
	}
}
