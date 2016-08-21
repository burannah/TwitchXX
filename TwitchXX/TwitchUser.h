#pragma once
#include "TwitchDef.h"
namespace TwitchXX
{
	///Twitch Users class
	/** This class represents twitch user object.*/
	class TwitchUser
	{
	public:
		///Equals operator
		/// Distinct users by id
		bool operator==(const TwitchUser& other) const
		{
			return _id == other._id;
		}


		///Less than operator
		/// Order users by creation date and last updated date
		bool operator<(const TwitchUser& other) const
		{
			return _created == other._created ? _updated < other._updated : _created < other._created;;
		}

		///@{
		/// Creation date
		const auto& Created() const { return _created; }
		/// Creation date as string ISO 8601
		std::wstring CreatedAsString() const { return DateToString(_created); };
		void Created(const std::wstring& cs) { _created = DateFromString(cs); };
		///@}


		///@{
		/// Updated date
		const auto& Updated() const { return _updated; }
		void Updated(const std::wstring& cs) { _updated = DateFromString(cs); };
		/// Updated date as string ISO 8601
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
		void DisplayName(const std::wstring& s) { _display_name = s; }
		const std::wstring& DisplayName() const { return _display_name; }
		///@}

		///@{
		/// Logo
		const std::wstring& Logo() const { return _logo; }
		void Logo(const std::wstring s) { _logo = s; }
		///@}

		///@{
		/// Type
		const std::wstring& Type() const { return _type; }
		void Type(const std::wstring s) { _type = s; }
		///@}

		///@{
		/// User's bio
		const std::wstring& Bio() const { return _bio; }
		void Bio(const std::wstring s) { _bio = s; }
		///@}

	private:
		Date _created;
		std::wstring _name;
		Date _updated;
		size_t _id = 0;
		std::wstring _display_name;
		std::wstring _logo;
		std::wstring _type; //TODO: to type?
		std::wstring _bio;
	};

	///Twitch blocked user class
	/** The same as TwithcUser but has some additional properties like date of block and block id*/
	class TwitchBlockedUser
	{
	public:

		///Equals operator
		/// Distinct block records by id
		bool operator==(const TwitchBlockedUser& other) const
		{
			return _block_id == other._block_id;
		}

		///Less than operator
		/// Order users by updated date
		bool operator<(const TwitchBlockedUser& other) const
		{
			return _block_updated == other._block_updated ? _user < other._user : _block_updated < other._block_updated;
		}

		///@{
		/// Timestamp of block
		const auto& BlockUpdated() const { return _block_updated; }
		void BlockUpdated(const std::wstring& cs) { _block_updated = DateFromString(cs); };
		/// Updated date as string ISO 8601
		std::wstring BlockUpdatedAsString() const { return DateToString(_block_updated); };
		///@}

		///@{
		/// Id
		size_t BlockedId() const { return _block_id; }
		void BlockedId(size_t id) { _block_id = id; }
		///@}

		///@{
		const TwitchUser& User() const { return _user; }
		TwitchUser& User() { return _user; }
		void User(const TwitchUser& user) { _user = user; }
		///@}

	private:
		size_t _block_id = 0;
		Date _block_updated;
		TwitchUser _user;
	};
}
