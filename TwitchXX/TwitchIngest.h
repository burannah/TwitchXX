#pragma once
#include "Property.h"

namespace TwitchXX
{
	class TwitchIngest
	{
	public:
		///Ingest name
		Property<std::wstring> Name;

		///Is default ingest flag
		Property<bool> Default;

		///Ingest id
		Property<size_t> Id;

		///Url template for current ingest
		Property<std::wstring> UrlTemplate;

		///Supported version information
		Property<std::wstring> Availability; //TODO: Introduce version type?


		///Less than operator
		/// Order users by creation date and last updated date
		bool operator<(const TwitchIngest& other) const
		{
			return Id.Get() < other.Id.Get();
		}

	};
}

