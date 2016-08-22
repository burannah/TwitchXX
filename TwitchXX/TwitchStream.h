#pragma once

#include <set>
#include <chrono>
#include <cpprest\details\basic_types.h>
#include "TwitchDef.h"
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

		static std::wstring type_to_string(Type t)
		{
			switch (t)
			{
			case TwitchStream::Type::all:
				return U("all");
			case TwitchStream::Type::live:
				return U("live");
			case TwitchStream::Type::playlist:
				return U("playlist");
			default:
				throw std::range_error("Stream type is not supported");
			}
		}

		///Channel offline flag
		Property<bool> Offline;
		///Game name
		Property<std::wstring> Game;
		///Number of viewers
		Property<size_t> Viewers;
		///Average FPS rate
		Property<double> Avg_Fps;
		///Delay
		Property<size_t> Delay;
		///Video_Height
		Property<size_t> Video_Height;
		///Is playlist flag
		Property<bool> Is_Playlist;
		///Created date
		Property<Date> Created;
		///Stream Id
		Property<unsigned long long> Id;
		///Channel
		TwitchChannel Channel;
		///Preview images
		ImageCollection Preview;


		///Operator less than
		bool operator<(const TwitchStream& other) const
		{
			return Id < other.Id;
		}

		///Operator equals
		bool operator==(const TwitchStream& other) const
		{
			return Id == other.Id;
		}

		///Channel's name
		const std::wstring& Name() const { return Channel.Name.Get(); }
	};


	///Temp helper
	std::wstring type_to_string(TwitchStream::Type);
}
