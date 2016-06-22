#pragma once
#include <string>
#include <set>
#include "TwitchDef.h"
#include "TwitchUser.h"

namespace TwitchXX
{
	class TwitchPost
	{
	public:
		TwitchPost();
		virtual ~TwitchPost();

		bool operator==(const TwitchPost& other) const
		{
			return _id == other._id;
		}

		bool operator<(const TwitchPost& other) const
		{
			return _created > other._created;
		}

		void Id(unsigned long long id) { _id = id; }
		unsigned long long Id() const { return _id; }

		void Created(const std::wstring& cs) { _created = DateFromString(cs); };
		const auto& Created() const { return _created; }
		std::wstring CreatedAsString() const { return DateToString(_created); };

		void Deleted(bool b) { _deleted = b; }
		bool Deleted() const { return _deleted; }

		void EndorsedCount(size_t c) { _endorsed_count = c; }
		size_t EndorsedCount() const { return _endorsed_count; }

		void EndorsedUsers(const std::set<std::wstring>& users) { _endorsed_users = users; }
		const std::set<std::wstring>& EndorsedUsers() const { return _endorsed_users; }

		void Body(const std::wstring& body) { _body = body; }
		const std::wstring& Body() const { return _body; }

		void Author(const TwitchUser& author) { _user = author; }
		const TwitchUser& Author() const { return _user; }

		void Tweet(const std::wstring& t) { _tweet = t; }
		const std::wstring& Tweet() const { return _tweet; }
	private:
		unsigned long long _id = 0;
		Date _created;
		bool _deleted = false;
		//vector<TwitchEmotes> _emotes; //TODO: not sure
		size_t _endorsed_count = 0;
		std::set<std::wstring> _endorsed_users;
		std::wstring _body;
		TwitchUser _user;
		std::wstring _tweet;
	};
}

