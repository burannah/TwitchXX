#pragma once
#include <string>
#include "TwitchStream.h"

namespace TwitchXX
{
	class TwitchFeaturedStream
	{
	public:
		TwitchFeaturedStream();
		virtual ~TwitchFeaturedStream();

		bool operator<(const TwitchFeaturedStream& other) const { return _stream < other._stream; }
		bool operator==(const TwitchFeaturedStream& other) const { return _stream == other._stream; }

		void Image(const std::wstring& s) { _image = s; }
		const std::wstring& Image() const { return _image; }

		void Text(const std::wstring& s) { _text = s; }
		const std::wstring& Text() const { return _text; }

		void Title(const std::wstring& s) { _title = s; }
		const std::wstring& Title() const { return  _title; }

		void Sponsored(bool s) { _sponsored = s; }
		bool Sponsored() const { return _sponsored; }

		void Scheduled(bool s) { _scheduled = s; }
		bool Scheduled() const { return _scheduled; }

		void Stream(const TwitchStream& s) { _stream = s; }
		const TwitchStream& Stream() const { return _stream; }


	private:
		std::wstring _image;
		std::wstring _text;
		std::wstring _title;
		bool _sponsored;
		bool _scheduled;
		TwitchXX::TwitchStream _stream;
	};
	
}
