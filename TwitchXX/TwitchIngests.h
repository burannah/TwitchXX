#pragma once
#include "TwitchRequest.h"
#include "TwitchIngest.h"

namespace TwitchXX
{
	class TwitchIngests : public TwitchRequest<TwitchIngest>
	{
	public:
		///Constructor
		explicit TwitchIngests(const std::shared_ptr<MakeRequest>& request)
			: TwitchRequest<TwitchIngest>(request)
		{
		}

		///Get the list of available ingetsts
		TwitchIngestsContainer GetIngests() const;
	};

	template<> TwitchIngest Create(const web::json::value& value); ///< Creates TwitchIngest object
}
