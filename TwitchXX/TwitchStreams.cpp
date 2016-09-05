#include "TwitchStreams.h"
#include "TwitchChannels.h"
#include <cpprest/uri_builder.h>
#include "JsonWrapper.h"
#include "TwitchException.h"

TwitchXX::TwitchStream TwitchXX::TwitchStreams::GetStream(const std::wstring & chanel) const
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

TwitchXX::TwitchStreamsContainer TwitchXX::TwitchStreams::GetStreams(size_t n, const options& op)
{
	static const size_t limit = 100; //TODO: To some global constants
	web::uri_builder builder(U("/streams"));
	options options{ op };
	auto it = options.find(U("offset"));  //TODO: do we need this?
	if (it != options.end()) options.erase(it);
	it = options.find(U("limit"));
	if (it != options.end()) options.erase(it);
	for (const auto& option : op)
	{
		builder.append_query(option.first, option.second);
	}
	builder.append_query(U("limit"), limit);

	TwitchStreamsContainer result;

	while (true)
	{
		TwitchStreamsContainer chunk;
		auto value = _request->get(builder.to_uri(), [this](const web::json::value& v) { TotalSize.Set(v.at(U("_total")).as_number().to_uint32()); });
		auto games = value.at(U("streams"));
		if (!games.is_null() && games.is_array())
		{
			for (const auto& game : games.as_array())
			{
				chunk.insert(Create<TwitchStream>(game));
			}
		}
		else
		{
			break;
		}

		result.insert(chunk.begin(), chunk.end());
		auto next = value.at(U("_links")).at(U("next"));
		if (result.size() < n && chunk.size() == limit && !next.is_null() && next.is_string())
		{
			builder = web::uri_builder(next.as_string());
		}
		else
		{
			break;
		}
	}

	return result;
}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::TwitchStreams::GetFeaturedStreams() const
{
	const static size_t limit = 100;
	web::uri_builder builder(U("/streams/featured"));
	builder.append_query(U("limit"), limit);
	TwitchContainer<TwitchFeaturedStream> chunk;
	for(;;)
	{
		auto value = _request->get(builder.to_uri());
		if (value.is_null())
		{
			break;
		}

		auto top = value.at(U("featured"));
		if (top.is_array())
		{

			for each (auto& object_descriptor in top.as_array())
			{
				chunk.insert(Create<TwitchFeaturedStream>(object_descriptor));
			}
		}
		else
		{
			break;
		}
		auto next = value.at(U("_links")).at(U("next"));
		if(!next.is_null() && next.is_string() && chunk.size() == limit)
		{
			builder = web::uri_builder(next.as_string());
		}
		else
		{
			break;
		}
	}
	return chunk;
}

std::tuple<size_t, size_t> TwitchXX::TwitchStreams::GetSummary(const std::wstring& game) const
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

//TODO: Not sure if it should be here. Probably should be moved to Users
TwitchXX::TwitchStreamsContainer TwitchXX::TwitchStreams::GetFollowedStreams(TwitchStream::Type type) const
{
	TwitchStreamsContainer result;
	web::uri_builder builder(U("/streams/followed"));
	builder.append_query(U("limit"), max_limit); //TODO: Check perfomance if limit is equal to actual number of channel followd (if < 100)
	if(type != TwitchStream::Type::none)
	{
		builder.append_query(U("stream_type"), TwitchStream::type_to_string(type));
	}
	for(;;)
	{
		TwitchStreamsContainer chunk;
		auto value = _request->get(builder.to_uri());
		if (value.is_null())
		{
			if(_request->status_code() == web::http::status_codes::Unauthorized)
			{
				throw TwitchException("Unable to get followed streams", _request->status_code());
			}
			else
			{
				break;
			}
		}

		auto top = value.at(U("streams"));
		if (top.is_array())
		{
			for each (auto& object_descriptor in top.as_array())
			{
				chunk.insert(Create<TwitchStream>(object_descriptor));
			}
			result.insert(chunk.begin(),chunk.end());
		}
		else
		{
			break;
		}
		auto next = value.at(U("_links")).at(U("next"));
		if (chunk.size() == max_limit && !next.is_null() && next.is_string())
		{
			builder = web::uri_builder(next.as_string());
		}
		else
		{
			break;
		}

#ifdef DEBUG
		std::wcout << "Total number of streams followed: " << value.at(U("_total")).as_integer()<<"\n";
#endif // DEBUG
	}
	return result;
}

template<>
TwitchXX::TwitchStream TwitchXX::Create(const web::json::value& obj) 
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
