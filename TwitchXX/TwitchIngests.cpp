#include "TwitchIngests.h"
#include "TwitchException.h"
#include "JsonWrapper.h"

TwitchXX::TwitchIngestsContainer TwitchXX::TwitchIngests::GetIngests() const
{
	try
	{
		TwitchIngestsContainer result;
		web::uri_builder builder{ U("/ingests/")};
		return GetObjectsArrayOnce<TwitchIngest>(builder, U("ingests"));
	}
	catch (TwitchException& e)
	{
		if (e.code() == web::http::status_codes::ServiceUnavailable)
		{
			throw TwitchException("Error retrieving ingest status", e.code());
		}
		throw;
	}

}

template <>
TwitchXX::TwitchIngest TwitchXX::Create<TwitchXX::TwitchIngest>(const web::json::value& value)
{
	TwitchIngest result;
	JsonWrapper w(value);

	result.Name.Set(*w[U("name")]);
	result.Default.Set(*w[U("default")]);
	result.Id.Set(*w[U("_id")]);
	result.UrlTemplate.Set(*w[U("url_template")]);
	result.Availability.Set(*w[U("availability")]);

	return result;
}
