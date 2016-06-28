#pragma once
#include "TwitchDef.h"

namespace TwitchXX
{
	///Twitch channel class
	/** Twitch channel object descriptor*/
	class TwitchChannel
	{
	public:
		///Equal operator
		/**
		* Channels are distinguished by id.
		*/
		bool operator==(const TwitchChannel& other) const
		{
			return _id == other._id;
		}
		///Operator less then
		/**
		* If two channels has the same number of followers - number of views considered.
		*/
		bool operator<(const TwitchChannel& other) const
		{
			return _followers == other._followers ? _views < other._views : _followers < other._followers;
		}

		///@{
		/** Mature content. */
		bool Mature() const { return _mature; }
		void Mature(bool b) { _mature = b; }
		///@}

		///@{
		/** Status. */
		const std::wstring& Status() const { return _status; }
		void Status(const std::wstring& s) { _status = s;  }
		///@}

		///@{
		/** Broadcaster language. */
		const std::wstring& BroadcasterLanguage() const { return _broadcaster_language; }
		void BroadcasterLanguage(const std::wstring& s) { _broadcaster_language = s; }
		///@}

		///@{
		/** Language. */
		const std::wstring& Language() const { return _language; }
		void Language(const std::wstring& s) { _language = s; }
		///@}

		///@{
		/** Display name. */
		const std::wstring& DisplayName() const { return _display_name; }
		void DisplayName(const std::wstring& s) { _display_name = s; }
		///@}

		///@{
		/** Game. */
		const std::wstring& Game() const { return _game; }
		void Game(const std::wstring& s) { _game = s; }
		///@}

		///@{
		/** Delay. */
		size_t Delay() const { return _delay; }
		void Delay(size_t delay) { _delay = delay; }
		///@}

		///@{
		/** Id. */
		size_t Id() const { return _id; }
		void Id(size_t id) { _id = id; }
		///@}

		///@{
		/** Name. */
		const std::wstring& Name() const { return _name; }
		void Name(const std::wstring& s) { _name = s; }
		///@}

		///@{
		/** Created date time. */
		void Created(const std::wstring& cs) { _created = DateFromString(cs); };
		const auto& Created() const { return _created; }
		/** Created date time as string. */
		std::wstring CreatedAsString() const { return DateToString(_created); };
		///@}

		///@{
		/** Update date time*/
		void Updated(const std::wstring& cs) { _updated = DateFromString(cs); };
		const auto& Updated() const { return _updated; }
		/** Updated date time as string*/
		std::wstring UpdatedAsString() const { return DateToString(_updated); };
		///@}

		///@{
		/** Logo. */
		const std::wstring& Logo() const { return _logo; }
		void Logo(const std::wstring& s) { _logo = s; }
		///@}

		///@{
		/** Banner. */
		const std::wstring& Banner() const { return _banner; }
		void Banner(const std::wstring& s) { _banner = s; }
		///@}

		///@{
		/** Video banner. */
		const std::wstring& VideoBanner() const { return _video_banner; }
		void VideoBanner(const std::wstring& s) { _video_banner = s; }
		///@}

		///@{
		/** Url. */
		const std::wstring& Url() const { return _url; }
		void Url(const std::wstring& s) { _url = s; }
		///@}

		///@{
		/** Background. */
		const std::wstring& Background() const { return _background; }
		void Background(const std::wstring& s) { _background = s; }
		///@}

		///@{
		/** Profile banner. */
		const std::wstring& ProfileBanner() const { return _profile_banner; }
		void ProfileBanner(const std::wstring& s) { _profile_banner = s; }
		///@}

		///@{
		/** Profile banner background color. */
		const std::wstring& ProfileBannerBkColor() const { return _profile_banner_background_color; }
		void ProfileBannerBkColor(const std::wstring& s) { _profile_banner_background_color = s; }
		///@}


		///@{
		/** Is partner? */
		bool Partner() const { return _partner; }
		void Partner(bool b) { _partner = b; }
		///@}

		///@{
		/** Number of views. */
		size_t Views() const { return _views; }
		void Views(size_t n) { _views = n; }
		///@}

		///@{
		/** Number of followers. */
		size_t Followers() const { return _followers; }
		void Followers(size_t n) { _followers = n; }
		///@}

		/**@{
		* SteamKey.
		*/
		void StreamKey(const std::wstring& s) { _stream_key = s; }
		const std::wstring& StreamKey() const { return _stream_key; }
		///@}

	private:
		bool _mature = false;
		std::wstring _status;
		std::wstring _broadcaster_language;
		std::wstring _language;
		std::wstring _display_name;
		std::wstring _game;
		size_t _delay = 0;
		size_t _id = 0;
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
		bool _partner = false;
		unsigned long _views = 0;
		unsigned long _followers = 0;
		std::wstring _stream_key;  //Only for authorized channels

	};
	///Default container for channels
	using TwitchChannelContainer = std::set<TwitchChannel>;

}
