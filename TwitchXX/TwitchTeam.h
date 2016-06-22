#pragma once
#include <string>
#include "TwitchDef.h"

namespace TwitchXX
{
	class TwitchTeam
	{
	public:
		TwitchTeam();
		virtual ~TwitchTeam();

		bool operator==(const TwitchTeam& other) const
		{
			return _id == other._id;
		}

		bool operator<(const TwitchTeam& other) const
		{
			return _created == other._created ? _updated < other._updated : _created < other._created;;
		}

		void Created(const std::wstring& cs) { _created = DateFromString(cs); };
		const auto& Created() const { return _created; }
		std::wstring CreatedAsString() const { return DateToString(_created); };

		void Updated(const std::wstring& cs) { _updated = DateFromString(cs); };
		const auto& Updated() const { return _updated; }
		std::wstring UpdatedAsString() const { return DateToString(_updated); };

		void Name(const std::wstring s) { _name = s; }
		const std::wstring& Name() const { return _name; }

		void Id(size_t id) { _id = id; }
		size_t Id() const { return _id; }

		void DisplayName(const std::wstring& s) { _display_name = s; }
		const std::wstring& DisplayName() const { return _display_name; }

		void Logo(const std::wstring s) { _logo = s; }
		const std::wstring& Logo() const { return _logo; }

		void Info(const std::wstring s) { _info = s; }
		const std::wstring& Info() const { return _info; }

		void Banner(const std::wstring s) { _banner = s; }
		const std::wstring& Banner() const { return _banner; }

		void Background(const std::wstring s) { _background = s; }
		const std::wstring& Background() const { return _background; }
	private:
		size_t _id;
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
