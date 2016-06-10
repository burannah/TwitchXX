#pragma once
#include "TwitchDef.h"

namespace TwitchXX
{
	class TwitchChannel
	{
	public:
		TwitchChannel();
		virtual ~TwitchChannel();

		bool operator==(const TwitchChannel& other) const
		{
			/*return _mature == other._mature && _status == other._status && _broadcaster_language == other._broadcaster_language && _language == other._language && _display_name == other._display_name &&
				_game == other._game && _delay == other._delay && _id == other._id && _name == other._name && _created == other._created && _updated == other._updated &&
				_logo == other._logo && _video_banner == other._video_banner && _url == other._url && _background == other._background && _profile_banner == other._profile_banner &&
				_profile_banner_background_color == other._profile_banner_background_color && _partner == other._partner && _views == other._views && _followers == other._followers;*/
			return _id == other._id;
		}

		bool operator<(const TwitchChannel& other) const
		{
			return _followers == other._followers ? _views < other._views : _followers < other._followers;
		}

		bool Mature() const { return _mature; }
		void Mature(bool b) { _mature = b; }

		const std::wstring& Status() const { return _status; }
		void Status(const std::wstring& s) { _status = s;  }

		const std::wstring& BroadcasterLanguage() const { return _broadcaster_language; }
		void BroadcasterLanguage(const std::wstring& s) { _broadcaster_language = s; }

		const std::wstring& Language() const { return _language; }
		void Language(const std::wstring& s) { _language = s; }

		const std::wstring& DisplayName() const { return _display_name; }
		void DisplayName(const std::wstring& s) { _display_name = s; }

		const std::wstring& Game() const { return _game; }
		void Game(const std::wstring& s) { _game = s; }

		size_t Delay() const { return _delay; }
		void Delay(size_t delay) { _delay = delay; }

		size_t Id() const { return _id; }
		void Id(size_t id) { _id = id; }

		const std::wstring& Name() const { return _name; }
		void Name(const std::wstring& s) { _name = s; }

		void Created(const std::wstring& cs) { _created = DateFromString(cs); };
		const auto& Created() const { return _created; }
		std::wstring CreatedAsString() const { return DateToString(_created); };

		void Updated(const std::wstring& cs) { _updated = DateFromString(cs); };
		const auto& Updated() const { return _updated; }
		std::wstring UpdatedAsString() const { return DateToString(_updated); };

		const std::wstring& Logo() const { return _logo; }
		void Logo(const std::wstring& s) { _logo = s; }

		const std::wstring& Banner() const { return _banner; }
		void Banner(const std::wstring& s) { _banner = s; }

		const std::wstring& VideoBanner() const { return _video_banner; }
		void VideoBanner(const std::wstring& s) { _video_banner = s; }

		const std::wstring& Url() const { return _url; }
		void Url(const std::wstring& s) { _url = s; }

		const std::wstring& Background() const { return _background; }
		void Background(const std::wstring& s) { _background = s; }

		const std::wstring& ProfileBanner() const { return _profile_banner; }
		void ProfileBanner(const std::wstring& s) { _profile_banner = s; }

		const std::wstring& ProfileBannerBkColor() const { return _profile_banner_background_color; }
		void ProfileBannerBkColor(const std::wstring& s) { _profile_banner_background_color = s; }

		bool Partner() const { return _partner; }
		void Partner(bool b) { _partner = b; }

		size_t Views() const { return _views; }
		void Views(size_t n) { _views = n; }

		size_t Followers() const { return _followers; }
		void Followers(size_t n) { _followers = n; }

		void StreamKey(const std::wstring& s) { _stream_key = s; }
		const std::wstring& StreamKey() const { return _stream_key; }

	private:
		bool _mature;
		std::wstring _status;
		std::wstring _broadcaster_language;
		std::wstring _language;
		std::wstring _display_name;
		std::wstring _game;
		size_t _delay;
		size_t _id;
		std::wstring _name;
		Date _created;
		Date _updated;
		std::wstring _logo;
		std::wstring _banner;
		std::wstring _video_banner;
		std::wstring _url;
		std::wstring _background;
		std::wstring _profile_banner;
		std::wstring _profile_banner_background_color;
		bool _partner;
		unsigned long _views;
		unsigned long _followers;
		std::wstring _stream_key;  //Only for authorized channels

	};

	using TwitchChannelContainer = std::set<TwitchChannel>;

}
