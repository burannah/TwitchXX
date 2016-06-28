#pragma once

#include <set>
#include "TwitchDef.h"
#include <chrono>
#include "TwitchChannel.h"

namespace TwitchXX
{
	///Twitch stream class
	/** This class represents twitch stream object.*/
	class TwitchStream
	{
	public:
		///Twitch stream type enum
		enum class Type
		{
			none, ///< Type is not available/applicable.
			all, ///< Any type
			playlist, ///< Playlist
			live ///< Live stream
		};

		///Default constructor
		TwitchStream();


		///Operator less than
		bool operator<(const TwitchStream& other) const
		{
			return _id < other._id;
		}

		///Operator equals
		bool operator==(const TwitchStream& other) const
		{
			return _id == other._id;
		}



		///@{
		/// Is stream offline?
		bool Offline() const { return _offline;	}
		void Offline(bool offline) { _offline = offline; }
		///@}

		///@{
		/// Number of viewers
		void Viewers(size_t n) { _viewers = { n }; }
		auto Viewers() const { return _viewers; }
		///@}

		///@{
		/// Game.
		void Game(const std::wstring& name) { _game = name; }
		const auto& Game() const { return _game; }
		///@}

		///@{
		/// Average frame rate
		void AvgFps(double fps) { _avg_fps = { fps }; }
		auto AvgFps() const { return _avg_fps; }
		///@}

		///@{
		/// Current delay
		void Delay(size_t seconds) { _delay = {seconds}; }
		auto Delay() const { return _delay; }
		///@}

		///@{
		/// Video height
		void VideoHeight(size_t height) { _video_height = height; }
		auto VideoHeight() const { return _video_height; }
		///@}

		///@{
		/// Is playlist?
		void IsPlaylist(bool value) { _is_playlist = value; }
    	auto IsPlaylist() const { return _is_playlist; }
		///@}

		///@{
		/// Creation date.
		const auto& Created() const { return _created; }
		void Created(const std::wstring& cs);
		/// Creation date as string ISO 8601
		std::wstring CreatedAsString() const;
		///@}

		///@{
		/// Id
		void Id(unsigned long long id) { _id = id; }
		auto Id() const { return _id; }
		///@}

		///@{
		/// TwitchChannel object for current stream
		const auto& Channel() const { return _channel; }
		void Channel(const TwitchChannel& create) { _channel = create;  }
		///@}

		///@{
		/// Preview
		const auto& Preview() const { return _preview; }
		void Preview(const ImageCollection& prvw) { _preview = prvw; }
		void Preview(ImageCollection&& prvw) { _preview = std::move(prvw); } //TODO: not sure
		///@}

		///Channel's name
		const std::wstring& Name() const { return _channel.Name(); }
	private:
		bool _offline;
		std::wstring _game;
		size_t _viewers;
		double _avg_fps;
		size_t _delay;
		size_t _video_height;
		bool _is_playlist;
		Date _created;
		unsigned long long _id;
		TwitchChannel _channel;
		ImageCollection _preview;
	};


	///Temp helper
	std::wstring type_to_string(TwitchStream::Type);
}
