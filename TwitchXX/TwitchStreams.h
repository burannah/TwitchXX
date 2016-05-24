#pragma once

#include <map>
#include <cpprest/json.h>
#include "TwitchStream.h"
#include "TwitchRequest.h"
#include "TwitchDef.h"



namespace TwitchXX
{
	class TwitchStreams : public TwitchRequest<TwitchStream>
	{
	public:
		TwitchStreams();
		virtual ~TwitchStreams();

		TwitchStream GetStream(const std::wstring& chanel) const;
		size_t GetTotalNumber();
		TwitchStreamsContainer GetStreams(size_t n, const options& opt);

	private:
		static web::uri_builder GetBuilder(const std::wstring & url = U("/streams"), const options & op = options());
		web::uri_builder GetBuilder(const std::wstring& url, const options& op, size_t offset, size_t limit) const;
	};

	template<> TwitchStream Create(const web::json::value& obj);
	ImageCollection CreateCollection(const web::json::value& json);
}

