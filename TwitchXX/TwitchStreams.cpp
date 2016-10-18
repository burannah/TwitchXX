#include "TwitchStreams.h"
#include "TwitchChannels.h"
#include <cpprest/uri_builder.h>
#include "JsonWrapper.h"
#include "TwitchException.h"

TwitchXX::TwitchStream TwitchXX::TwitchStreams::GetStream(const utility::string_t & chanel) const
{
	web::uri_builder builder(U("/streams/") + chanel + U("/"));
	auto value = _request->get(builder.to_uri());
	if (value.is_null())
	{
		throw std::runtime_error("No objects were returned");
	}

	return Create<TwitchStream>(value.at(U("stream")));
}
size_t TwitchXX::TwitchStreams::UpdateTotal() const
{
	web::uri_builder builder(U("/streams"));
	auto value = _request->get(builder.to_uri());
	builder.append_query(U("limit"), 1);
	TotalSize.Set(value.at(U("_total")).as_number().to_uint32());
	return TotalSize.Get();
};

TwitchXX::TwitchStreamsContainer TwitchXX::TwitchStreams::GetStreams(unsigned int n, const options& op) const
{
	static const size_t limit = 100; //TODO: To some global constants
	web::uri_builder builder(U("/streams"));
	AddOption(builder, op, U("offset"));
	//AddOption(builder, op, U("limit"));
	AddOption(builder, op, U("game"));
	AddOption(builder, op, U("channel"));
	AddOption(builder, op, U("client_id"));
	AddOption(builder, op, U("stream_type"));
	AddOption(builder, op, U("language"));
	builder.append_query(U("limit"), limit);

	return GetObjectsArrayByNext<TwitchStream>(builder, U("streams"));
}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::TwitchStreams::GetFeaturedStreams() const
{
	const static size_t limit = 100;
	web::uri_builder builder(U("/streams/featured"));
	builder.append_query(U("limit"), limit);
	return GetObjectsArrayByNext<TwitchFeaturedStream>(builder, U("featured"));
}

std::tuple<unsigned int, unsigned int> TwitchXX::TwitchStreams::GetSummary(const utility::string_t& game) const
{
	web::uri_builder builder(U("/streams/summary"));
	if (game.length() > 0)
	{
		builder.append_query(U("game"), game);
	}
	auto value = _request->get(builder.to_uri());
	if (value.is_null())
	{
		throw std::runtime_error("Can not get streams summary!");
	}

	auto viewers = value.at(U("viewers")).as_number().to_uint32();
	auto channels = value.at(U("channels")).as_number().to_uint32();

	return std::make_tuple(viewers, channels);
}

TwitchXX::TwitchStreamsContainer TwitchXX::TwitchStreams::GetFollowedStreams(TwitchStream::Type type) const
{
	TwitchStreamsContainer result;
	web::uri_builder builder(U("/streams/followed"));
	builder.append_query(U("limit"), max_limit); //TODO: Check perfomance if limit is equal to actual number of channel followd (if < 100)
	if(type != TwitchStream::Type::none)
	{
		builder.append_query(U("stream_type"), TwitchStream::type_to_string(type));
	}

	return GetObjectsArrayByNext<TwitchStream>(builder, U("streams"));
}

template<>
TwitchXX::TwitchStream TwitchXX::Create<TwitchXX::TwitchStream>(const web::json::value& obj)
{
	TwitchStream stream;
	if (obj.is_null())
	{
		stream.Offline.Set(true);
		return stream;
	}

	JsonWrapper wrapper (obj);

	stream.Game.Set(*wrapper[U("game")]);
	stream.Viewers.Set(*wrapper[U("viewers")]);
	stream.Avg_Fps.Set(*wrapper[U("average_fps")]);
	stream.Delay.Set(*wrapper[U("delay")]);
	stream.Video_Height.Set(*wrapper[U("video_height")]);
	stream.Is_Playlist.Set(*wrapper[U("is_playlist")]);
	stream.Created.from_string(*wrapper[U("created_at")]);
	stream.Id.Set(*wrapper[U("_id")]);
	stream.Channel = Create<TwitchChannel>(obj.at(U("channel")));
	stream.Preview = CreateCollection(obj.at(U("preview")));

	return stream;
}

template <>
TwitchXX::TwitchFeaturedStream TwitchXX::Create<TwitchXX::TwitchFeaturedStream>(const web::json::value& obj)
{
	TwitchFeaturedStream stream;
	JsonWrapper wrapper(obj);

	stream.Image.Set(*wrapper[U("image")]);
	stream.Text.Set(*wrapper[U("text")]);
	stream.Title.Set(*wrapper[U("title")]);
	stream.Sponsored.Set(*wrapper[U("sponsored")]);
	stream.Scheduled.Set(*wrapper[U("scheduled")]);
	stream.Stream = Create<TwitchStream>(obj.at(U("stream")));

	return stream;
}
