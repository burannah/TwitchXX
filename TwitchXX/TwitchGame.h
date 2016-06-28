#pragma once
#include <set>
#include <map>
#include "TwitchDef.h"

namespace TwitchXX
{
	///Twitch featured stream object
	/** This class represents twitch featured stream object. Almost like normal stream object, but with some additional fields*/
	class TwitchGame
	{
	public:
		///Default construcotr
		TwitchGame();
		///Default copy constructor
		TwitchGame(const TwitchGame& other) = default;
		///Default move constructor
		TwitchGame(TwitchGame&& other) = default;

		///Default copy assigment
		TwitchGame& operator=(const TwitchGame&) = default;
		///Default move assigment
		TwitchGame& operator=(TwitchGame&&) = default;


		///Less than operator
		bool operator<(const TwitchGame& other) const
		{
			return _id < other._id;
		}

		///Equals operator
		bool operator==(const TwitchGame& other) const
		{
			return _id == other._id;
		}

		///@{
		/// Name.
		std::wstring Name() const { return _name; }
		void Name(const std::wstring& name) { _name = name; }
		///@}

		///@{
		/// Channels
		size_t Channels() const { return _channels; }
		void Channels(size_t count) { _channels = count; }
		///@}

		///@{
		/// Viewers.
		size_t Viewers() const { return _viewers; }
		void Viewers(size_t count) { _viewers = count; }
		///@}

		///@{
		/// Id
		size_t Id() const { return _id; }
		void Id(size_t id) { _id = id; }
		///@}

		///@{
		/// Giantbomb Id.
		size_t Giantbomb_Id() const { return _giantbomb_id; }
		void Giantbomb_Id(size_t id) { _giantbomb_id = id; }
		///@}

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
		std::wstring _name;
		size_t _channels;
		size_t _viewers;
		size_t _id;
		size_t _giantbomb_id;
		ImageCollection _box;
		ImageCollection _logo;
	};
}

