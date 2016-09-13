#include "TwitchSearch.h"

TwitchXX::TwitchChannelsContainer TwitchXX::TwitchSearch::SearchChannels(const utility::string_t& query, unsigned int limit, unsigned int offset)
{
	web::uri_builder builder(U("/search/channels"));
	builder.append_query(U("query"), query);
	if (limit != 25) builder.append_query(U("limit"), limit);
	if (offset != 0) builder.append_query(U("offset"), offset);
	return Search<TwitchChannel>(builder);
}

TwitchXX::TwitchStreamsContainer TwitchXX::TwitchSearch::SearchStreams(const utility::string_t& query, unsigned int limit, unsigned int offset)
{
	web::uri_builder builder(U("/search/streams"));
	builder.append_query(U("query"), query);
	if (limit != 25) builder.append_query(U("limit"), limit);
	if (offset != 0) builder.append_query(U("offset"), offset);
	return Search<TwitchStream>(builder);
}

TwitchXX::TwitchGamesContainer TwitchXX::TwitchSearch::SearchGames(const utility::string_t& query, unsigned int limit, unsigned int offset)
{
	web::uri_builder builder(U("/search/games"));
	builder.append_query(U("query"), query);
	if (limit != 25) builder.append_query(U("limit"), limit);
	if (offset != 0) builder.append_query(U("offset"), offset);
	return Search<TwitchGame>(builder);
}
