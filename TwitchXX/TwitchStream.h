#pragma once

#include <set>
#include "TwitchDef.h"
#include <chrono>
#include "TwitchChannel.h"

namespace TwitchXX
{
	class TwitchStream
	{
	public:
		enum class Type
		{
			none,
			all,
			playlist,
			live
		};

		TwitchStream();
		virtual ~TwitchStream();

		bool operator<(const TwitchStream& other) const
		{
			return _id < other._id;
		}

		bool operator==(const TwitchStream& other) const
		{
			/*return _offline == other._offline &&_created == other._created && _viewers == other._viewers && _avg_fps == other._avg_fps && 
				_channel == other._channel && _game == other._game && _delay == other._delay && _video_height == other._video_height && 
				_is_playlist == other._is_playlist && _preview == other._preview;*/
			return _id == other._id;
		}

		bool operator!=(const TwitchStream& other) const
		{
			return !(*this == other);
		}


		bool Offline() const { return _offline;	}
		void Offline(bool offline = true) { _offline = offline; }

		void Viewers(size_t n) { _viewers = { n }; }
		auto Viewers() const { return _viewers; }

		void Game(const std::wstring& name) { _game = name; }
		const auto& Game() const { return _game; }

		void AvgFps(double fps) { _avg_fps = { fps }; }
		auto AvgFps() const { return _avg_fps; }

		void Delay(size_t seconds) { _delay = {seconds}; }
		auto Delay() const { return _delay; }

		void VideoHeight(size_t height) { _video_height = height; }
		auto VideoHeight() const { return _video_height; }

		void IsPlaylist(bool value) { _is_playlist = value; }
    	auto IsPlaylist() const { return _is_playlist; }

		void Created(const std::wstring& cs);
		const auto& Created() const { return _created; }
		std::wstring CreatedAsString() const;

		void Id(size_t id) { _id = id; }
		auto Id() const { return _id; }

		void Channel(const TwitchChannel& create) { _channel = create;  }
		const auto& Channel() const { return _channel; }

		void Preview(const ImageCollection& prvw) { _preview = prvw; }
		void Preview(ImageCollection&& prvw) { _preview = std::move(prvw); } //TODO: not sure
		const auto& Preview() const { return _preview; }

		//Custom:
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
		size_t _id;
		TwitchChannel _channel;
		ImageCollection _preview;
	};

	using TwitchStreamsContainer = std::set<TwitchStream>;

	std::wstring type_to_string(TwitchStream::Type);
}
