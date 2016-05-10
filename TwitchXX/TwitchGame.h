#pragma once
#include <map>

namespace TwitchXX
{
	class TwitchGame
	{
	public:
	friend class TwitchGames;
	using ImageCollection = std::map<std::wstring, std::wstring>;

	TwitchGame();
	TwitchGame(const TwitchGame& other);
	TwitchGame(TwitchGame&& other);
	virtual ~TwitchGame();

	TwitchGame& operator=(const TwitchGame& other);
	TwitchGame& operator=(TwitchGame&& other);

	std::wstring Name() const { return _name; }
	unsigned int Channels() const { return _channels; }
	unsigned int Viewers() const { return _viewers; }
	unsigned intId() const { return _id; }
	unsigned int Giantbomb_Id() const { return _giantbomb_id; }
	const ImageCollection& Box() const { return _box; }
	const ImageCollection& Logo() const { return _logo; }

	private:
	std::wstring _name;
	unsigned int _channels;
	unsigned int _viewers;
	unsigned int _id;
	unsigned int _giantbomb_id;
	ImageCollection _box;
	ImageCollection _logo;

	void Name(const std::wstring& name) { _name = name; }
	void Channels(int count) { _channels = count; }
	void Viewers(int count) { _viewers = count; }
	void Id(int id) { _id = id; }
	void Giantbomb_Id(int id) { _giantbomb_id = id; }
	void Box(const ImageCollection& col) { _box = col; }
	void Logo(const ImageCollection& col) { _logo = col; }
	ImageCollection& Box() { return _box; }
	ImageCollection& Logo() { return _logo; }

	void swap(TwitchGame& other) noexcept;
	void swap(const TwitchGame& other);

	};

	using TwitchGamesContainer = std::map<std::wstring, TwitchGame>;
}

