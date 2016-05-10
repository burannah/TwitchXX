#include "TwitchGame.h"
#include <utility>


TwitchXX::TwitchGame::TwitchGame(): _channels(0), _viewers(0), _id(0), _giantbomb_id(0),
	_box({ { L"small", L"" },{ L"medium", L"" },{ L"large", L"" },{ L"template",L"" } }),
	_logo({ { L"small", L"" },{ L"medium", L"" },{ L"large", L"" },{ L"template",L"" } })
{
}

TwitchXX::TwitchGame::TwitchGame(const TwitchGame& other) : TwitchGame()
{
	this->swap(other);
}

TwitchXX::TwitchGame::TwitchGame(TwitchGame&& other) : TwitchGame()
{
	*this = other;
#if 0
  	_name = std::move(other._name);
	_box = std::move(other._box);
	_logo = std::move(other._logo);
	_channels = other._channels;
	_viewers = other._channels;
	_id = other._channels;
	_giantbomb_id = other._giantbomb_id;

#endif
}

TwitchXX::TwitchGame::~TwitchGame()
{
}

TwitchXX::TwitchGame& TwitchXX::TwitchGame::operator=(const TwitchGame& other)
{
	if (this == &other) return *this;
	this->swap(other);
	return *this;
}

TwitchXX::TwitchGame& TwitchXX::TwitchGame::operator=(TwitchGame&& other)
{
	_name = std::move(other._name);
	_box = std::move(other._box);
	_logo = std::move(other._logo);
	_channels = other._channels;
	_viewers = other._channels;
	_id = other._channels;
	_giantbomb_id = other._giantbomb_id;

	return *this;
}

void TwitchXX::TwitchGame::swap(TwitchGame& other) noexcept
{
	std::swap(_name, other._name);
	std::swap(_channels, other._channels);
	std::swap(_viewers, other._viewers);
	std::swap(_id, other._id);
	std::swap(_giantbomb_id, other._giantbomb_id);
	std::swap(_box, other._box);
	std::swap(_logo, other._logo);
}

void TwitchXX::TwitchGame::swap(const TwitchGame& other)
{
	_name = other._name;
	_box = other._box;
	_logo = other._logo;
	_channels = other._channels;
	_viewers = other._channels;
	_id = other._channels;
	_giantbomb_id = other._giantbomb_id;
}
