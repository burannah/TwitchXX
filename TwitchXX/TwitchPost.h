#pragma once
#include <string>
#include <set>
#include "TwitchDef.h"
#include "TwitchUser.h"

namespace TwitchXX
{
	///Twitch post object
	/** This class represents twitch post (from channel feed) object.*/
	class TwitchPost
	{
	public:
		///Equals operator
		/// Distinct by Id
		bool operator==(const TwitchPost& other) const
		{
			return _id == other._id;
		}

		///Less than operator
		/// Order by creation date
		bool operator<(const TwitchPost& other) const
		{
			return _created > other._created;
		}

		///@{
		/// Id
		void Id(unsigned long long id) { _id = id; }
		unsigned long long Id() const { return _id; }
		///@}

		///@{
		/// Creation date
		const auto& Created() const { return _created; }
		void Created(const std::wstring& cs) { _created = DateFromString(cs); };
		/// Creatiion date as string ISO 8601
		std::wstring CreatedAsString() const { return DateToString(_created); };
		///@}

		///@{
		/// Is Deleted?
		void Deleted(bool b) { _deleted = b; }
		bool Deleted() const { return _deleted; }
		///@}

		///@{
		/// Count of post endorsements
		size_t EndorsedCount() const { return _endorsed_count; }
		void EndorsedCount(size_t c) { _endorsed_count = c; }
		///@}

		///@{
		/// Endorsed users id's
		const std::set<unsigned long long>& EndorsedUsers() const { return _endorsed_users; }
		void EndorsedUsers(const std::set<unsigned long long>& users) { _endorsed_users = users; }
		///@}

		///@{
		/// Post's body (content)
		const std::wstring& Body() const { return _body; }
		void Body(const std::wstring& body) { _body = body; }
		///@}

		///@{
		/// Post's author (as TwitchUser object)
		const TwitchUser& Author() const { return _user; }
		void Author(const TwitchUser& author) { _user = author; }
		///@}

		///@{
		/// Tweet url (if post was shared)
		const std::wstring& Tweet() const { return _tweet; }
		void Tweet(const std::wstring& t) { _tweet = t; }
		///@}
	private:
		unsigned long long _id = 0;
		Date _created;
		bool _deleted = false;
		//vector<TwitchEmotes> _emotes; //TODO: not sure
		size_t _endorsed_count = 0;
		std::set<unsigned long long> _endorsed_users;
		std::wstring _body;
		TwitchUser _user;
		std::wstring _tweet;
	};
}

