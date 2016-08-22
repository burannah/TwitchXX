#pragma once
#include <set>
#include <map>
#include "TwitchDef.h"
#include "Property.h"

namespace TwitchXX
{
	///Twitch featured stream object
	/** This class represents twitch featured stream object. Almost like normal stream object, but with some additional fields*/
	class TwitchGame
	{
	public:
		Property<std::wstring> Name;  ///Game's name
		Property<size_t> Channels;	  ///Number of broadcasting channgels
		Property<size_t> Viewers;	  ///Numeber of viewers
		Property<size_t> Id;		  ///Game's Id
		Property<size_t> GiantbombId; ///Giantbomb id



		///Less than operator
		bool operator<(const TwitchGame& other) const
		{
			return Id.Get() < other.Id.Get();
		}

		///Equals operator
		bool operator==(const TwitchGame& other) const
		{
			return Id.Get() == other.Id.Get();
		}

		///@{
		/// Boxes.
		const ImageCollection& Box() const { return _box; }
		void Box(const ImageCollection& col) { _box = col; }
		void Box(ImageCollection&& col) { _box = std::move(col); }
		ImageCollection& Box() { return _box; }
		///@}

		///@{
		/// Logos.
		const ImageCollection& Logo() const { return _logo; }
		void Logo(const ImageCollection& col) { _logo = col; }
		void Logo(ImageCollection&& col) { _logo = std::move(col); }
		ImageCollection& Logo() { return _logo; }
		///@}

	private:
		ImageCollection _box;
		ImageCollection _logo;
	};
}

