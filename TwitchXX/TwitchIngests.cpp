#include "TwitchIngests.h"
#include "TwitchException.h"
#include "JsonWrapper.h"

TwitchXX::TwitchIngestsContainer TwitchXX::TwitchIngests::GetIngests() const
{
	try
	{
		TwitchIngestsContainer result;
		web::uri_builder builder{ U("/ingests/")};

		auto response = _request->put(builder.to_uri());
		auto ingests = response.at(U("ingests"));
		if(ingests.is_null() || !ingests.is_array())
		{
			throw TwitchException("Wrong repsonse format", _request->status_code());
		}
		for (const auto& ingest : ingests.as_array())
		{
			result.insert(Create<TwitchIngest>(ingest));
		}

		return result;
	}
	catch (TwitchException e)
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
