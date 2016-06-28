#pragma once
#include <string>
#include "TwitchStream.h"

namespace TwitchXX
{
	///Twitch featured stream object
	/** This class represents twitch featured stream object. Almost like normal stream object, but with some additional fields*/
	class TwitchFeaturedStream
	{
	public:
		///Less than opeartor
		bool operator<(const TwitchFeaturedStream& other) const { return _stream < other._stream; }
		///Equals operator
		bool operator==(const TwitchFeaturedStream& other) const { return _stream == other._stream; }

		///@{
		/// Image.
		const std::wstring& Image() const { return _image; }
		void Image(const std::wstring& s) { _image = s; }
		///@}

		///@{
		/// Text.
		const std::wstring& Text() const { return _text; }
		void Text(const std::wstring& s) { _text = s; }
		///@}

		///@{
		/// Title.
		const std::wstring& Title() const { return  _title; }
		void Title(const std::wstring& s) { _title = s; }
		///@}

		///@{
		/// Is sponsored?
		bool Sponsored() const { return _sponsored; }
		void Sponsored(bool s) { _sponsored = s; }
		///@}

		///@{
		/// Is scheduled?
		bool Scheduled() const { return _scheduled; }
		void Scheduled(bool s) { _scheduled = s; }
		///@}

		///@{
		/// Underlying stream object (real stream)
		const TwitchStream& Stream() const { return _stream; }
		void Stream(const TwitchStream& s) { _stream = s; }
		///@}


	private:
		std::wstring _image;
		std::wstring _text;
		std::wstring _title;
		bool _sponsored = false;
		bool _scheduled = false;
		TwitchXX::TwitchStream _stream;
	};
	
}
