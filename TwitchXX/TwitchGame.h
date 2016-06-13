#pragma once
#include <set>
#include <map>
#include "TwitchDef.h"

namespace TwitchXX
{
	class TwitchGame
	{
	public:
		TwitchGame();
		TwitchGame(const TwitchGame& other);
		TwitchGame(TwitchGame&& other) noexcept;
		virtual ~TwitchGame() noexcept;

		TwitchGame& operator=(const TwitchGame& other);
		TwitchGame& operator=(TwitchGame&& other) noexcept;

		bool operator<(const TwitchGame& other) const
		{
			return _id < other._id;
		}

		bool operator==(const TwitchGame& other) const
		{
			/*return _name == other._name && _channels == other._channels && _viewers == other._viewers && _id == other._id
					&& _giantbomb_id == other._giantbomb_id && _box == other._box && _logo == other._logo;*/
			return _id == other._id;
		}

		bool operator!=(const TwitchGame& other) const
		{
			return !(*this == other);
		}

		std::wstring Name() const { return _name; }
		size_t Channels() const { return _channels; }
		size_t Viewers() const { return _viewers; }
		size_t Id() const { return _id; }
		size_t Giantbomb_Id() const { return _giantbomb_id; }
		const ImageCollection& Box() const { return _box; }
		const ImageCollection& Logo() const { return _logo; }

		void Name(const std::wstring& name) { _name = name; }
		void Channels(size_t count) { _channels = count; }
		void Viewers(size_t count) { _viewers = count; }
		void Id(size_t id) { _id = id; }
		void Giantbomb_Id(size_t id) { _giantbomb_id = id; }
		void Box(const ImageCollection& col) { _box = col; }
		void Box(ImageCollection&& col) { _box = std::move(col); }
		void Logo(const ImageCollection& col) { _logo = col; }
		void Logo(ImageCollection&& col) { _logo = std::move(col); }
		ImageCollection& Box() { return _box; }
		ImageCollection& Logo() { return _logo; }

	private:
		std::wstring _name;
		size_t _channels;
		size_t _viewers;
		size_t _id;
		size_t _giantbomb_id;
		ImageCollection _box;
		ImageCollection _logo;



		void swap(TwitchGame& other);
		void copy(const TwitchGame& other);

	};
}

