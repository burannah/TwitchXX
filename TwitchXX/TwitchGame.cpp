#include "TwitchGame.h"
#include <utility>


TwitchXX::TwitchGame::TwitchGame(): _channels(0), _viewers(0), _id(0), _giantbomb_id(0),
	_box({ { L"small", L"" },{ L"medium", L"" },{ L"large", L"" },{ L"template",L"" } }),
	_logo({ { L"small", L"" },{ L"medium", L"" },{ L"large", L"" },{ L"template",L"" } })
{
}

TwitchXX::TwitchGame::TwitchGame(const TwitchGame& other) : TwitchGame()
{
	this->copy(other);
}

TwitchXX::TwitchGame::TwitchGame(TwitchGame&& other) noexcept : TwitchGame()
{
	this->swap(other);
}

TwitchXX::TwitchGame::~TwitchGame() noexcept
{
}

TwitchXX::TwitchGame& TwitchXX::TwitchGame::operator=(const TwitchGame& other)
{
	if (this == &other)
	{
		this->copy(other);
	}
	return *this;
}

TwitchXX::TwitchGame& TwitchXX::TwitchGame::operator=(TwitchGame&& other)
{
	this->swap(other);
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

void TwitchXX::TwitchGame::copy(const TwitchGame& other)
{
	_name = other._name;
	_box = other._box;
	_logo = other._logo;
	_channels = other._channels;
	_viewers = other._viewers;
	_id = other._id;
	_giantbomb_id = other._giantbomb_id;
}
