#pragma once
#include <string>
#include "TwitchDef.h"

namespace TwitchXX
{
	///Twitch team class
	/** This class represents twitch team object.*/
	class TwitchTeam
	{
	public:
		///Operator equals
		/// Distinc objects by Id
		bool operator==(const TwitchTeam& other) const
		{
			return _id == other._id;
		}


		///Operator less than
		/// Order teams by creation date and last updated date
		bool operator<(const TwitchTeam& other) const
		{
			return _created == other._created ? _updated < other._updated : _created < other._created;;
		}

		///@{
		/// Creation date
		const auto& Created() const { return _created; }
		void Created(const std::wstring& cs) { _created = DateFromString(cs); };
		/// Creation date as string ISO 8601
		std::wstring CreatedAsString() const { return DateToString(_created); };
		///@}

		///@{
		/// Update date
		const auto& Updated() const { return _updated; }
		void Updated(const std::wstring& cs) { _updated = DateFromString(cs); };
		/// Update date as string ISO 8601
		std::wstring UpdatedAsString() const { return DateToString(_updated); };
		///@}

		///@{
		/// Name
		const std::wstring& Name() const { return _name; }
		void Name(const std::wstring s) { _name = s; }
		///@}

		///@{
		/// Id
		size_t Id() const { return _id; }
		void Id(size_t id) { _id = id; }
		///@}

		///@{
		/// Display name
		const std::wstring& DisplayName() const { return _display_name; }
		void DisplayName(const std::wstring& s) { _display_name = s; }
		///@}

		///@{
		/// Logo
		const std::wstring& Logo() const { return _logo; }
		void Logo(const std::wstring s) { _logo = s; }
		///@}

		///@{
		/// Info
		const std::wstring& Info() const { return _info; }
		void Info(const std::wstring s) { _info = s; }
		///@}

		///@{
		/// Banner
		const std::wstring& Banner() const { return _banner; }
		void Banner(const std::wstring s) { _banner = s; }
		///@}

		///@{
		/// Background
		const std::wstring& Background() const { return _background; }
		void Background(const std::wstring s) { _background = s; }
		///@}

	private:
		size_t _id = 0;
		std::wstring _name;
		std::wstring _info;
		std::wstring _display_name;
		Date _created;
		Date _updated;
		std::wstring _logo;
		std::wstring _banner;
		std::wstring _background;

	};
	
}
