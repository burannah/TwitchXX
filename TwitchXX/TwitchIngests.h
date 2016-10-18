#pragma once
#include "TwitchRequest.h"
#include "TwitchIngest.h"

namespace TwitchXX
{
	class TwitchIngests : public TwitchRequest
	{
	public:
		///Constructor
		explicit TwitchIngests(MakeRequest *request)
			: TwitchRequest(request)
		{
		}

		///Get the list of available ingetsts
		TwitchIngestsContainer GetIngests() const;
	};

	template<> TwitchIngest Create(const web::json::value& value); ///< Creates TwitchIngest object
}
