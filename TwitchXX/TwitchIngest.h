#pragma once
#include "Property.h"

namespace TwitchXX
{
	class TwitchIngest
	{
	public:
		///Ingest name
		Property<utility::string_t> Name;

		///Is default ingest flag
		Property<bool> Default;

		///Ingest id
		Property<unsigned int> Id;

		///Url template for current ingest
		Property<utility::string_t> UrlTemplate;

		///Supported version information
		Property<utility::string_t> Availability; //TODO: Introduce version type?


		///Less than operator
		/// Order users by creation date and last updated date
		bool operator<(const TwitchIngest& other) const
		{
			return Id.Get() < other.Id.Get();
		}

	};
}

