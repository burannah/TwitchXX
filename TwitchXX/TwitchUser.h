#pragma once
#include "TwitchDef.h"
namespace TwitchXX
{
	class TwitchUser
	{
	public:
		TwitchUser();
		virtual ~TwitchUser();

		bool operator==(const TwitchUser& other) const
		{
			return _id == other._id;
		}

		bool operator<(const TwitchUser& other) const
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

		void Type(const std::wstring s) { _type = s; }
		const std::wstring& Type() const { return _type; }

		void Bio(const std::wstring s) { _bio = s; }
		const std::wstring& Bio() const { return _bio; }
	private:
		Date _created;
		std::wstring _name;
		Date _updated;
		size_t _id;
		std::wstring _display_name;
		std::wstring _logo;
		std::wstring _type; //TODO: to type?
		std::wstring _bio;
	};
}
