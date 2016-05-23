#pragma once

#include <map>
#include "TwitchStream.h"
#include "TwitchRequest.h"

namespace TwitchXX
{
	class TwitchStreams : public TwitchRequest<TwitchStream>
	{
	public:
		using options = std::map<std::wstring, std::wstring>;
		TwitchStreams();
		virtual ~TwitchStreams();

		TwitchStream GetStream(const std::wstring& chanel);
		TwitchStreamsContainer GetStreams(const options& opt = options());

	private:
		virtual web::uri_builder GetBuilder(size_t limit, size_t offset);
	};
}

