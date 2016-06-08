#pragma once

#include <map>
#include <cpprest/json.h>
#include "TwitchStream.h"
#include "TwitchRequest.h"
#include "TwitchDef.h"
#include "TwitchFeaturedStream.h"


namespace TwitchXX
{
	class TwitchStreams : public TwitchRequest<TwitchStream>
	{
	public:
		TwitchStreams();
		virtual ~TwitchStreams();

		TwitchStream GetStream(const std::wstring& chanel) const;
		size_t GetTotalNumber();
		TwitchStreamsVector GetStreams(size_t n, const options& opt);
		TwitchFeaturedStreamsContainer GetFeaturedStreams();
		std::tuple<size_t, size_t> GetSummary(const std::wstring& game = std::wstring());
		TwitchStreamsContainer GetFollowedStreams(TwitchStream::Type type = TwitchStream::Type::none);
	private:
		static web::uri_builder GetBuilder(const std::wstring & url = U("/streams"), const options & op = options());
		web::uri_builder GetBuilder(const std::wstring& url, const options& op, size_t offset, size_t limit) const;
	};

	template<> TwitchStream Create(const web::json::value& obj);
	ImageCollection CreateCollection(const web::json::value& json);

	template<> TwitchFeaturedStream Create(const web::json::value& obj);
}

