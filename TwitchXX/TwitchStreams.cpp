#include "TwitchStreams.h"
#include "TwitchChannels.h"
#include <cpprest/uri_builder.h>
#include "JsonWrapper.h"
#include "TwitchException.h"

TwitchXX::TwitchStream TwitchXX::TwitchStreams::GetStream(const std::wstring & chanel) const
{
	auto builder = GetBuilder(U("/streams/") + chanel + U("/"));
	auto value = (*_request)(builder.to_uri());
	if (value.is_null())
	{
		throw std::runtime_error("No objects were returned");
	}

	return Create<TwitchStream>(value.at(U("stream")));
}
size_t TwitchXX::TwitchStreams::GetTotalNumber()
{
	options op = { {U("limit"), U("1")}, {U("offset"), U("0")} };
	FetchChunk(GetBuilder(U("/streams"),op).to_uri(), U("streams")); return _total_size;
};

TwitchXX::TwitchStreamsVector TwitchXX::TwitchStreams::GetStreams(size_t n, const options & op)
{
	auto offset = 0;
	//Updating limit
	_limit = n < max_limit ? n : max_limit;
	auto max_objects = n == 0 ? _total_size : n;
	const auto max_retries = 3;
	auto retries = 0;
	while (_objects.size() < max_objects)
	{
		int count = _objects.size();
		auto chunk = FetchChunk(GetBuilder(U("/streams"), op, _offset, _limit).to_uri(), U("streams"));
		_objects.insert(chunk.begin(), chunk.end());
		if (chunk.size() == 0 || _objects.size() == count)
		{
			++retries;
		}
		else
		{
			retries = 0;
		}
		// "Trembling" protection
		_offset = count + static_cast<size_t>(chunk.size() * 0.8);
		_offset = std::min(_objects.size(), _offset);
		if (_offset + _limit > _total_size)
		{
			_offset = _total_size < _limit ? 0 : _total_size - _limit;
		}
		if (retries >= max_retries)
		{
			break;
		}
		std::wcout << "Before=" << count << " After=" << _objects.size() << " Chunk=" << chunk.size() << " Offset=" << _offset << " Total=" << _total_size << " Retries = " << retries << std::endl;
	}

	// Objects are sorted by names. We need to return mast watched of them == sorted by the number of viewers.
	// So here comes some trick
	std::vector<TwitchStream> v(_objects.begin(), _objects.end());
	std::sort(v.begin(), v.end(), [](const TwitchStream& a, const TwitchStream& b) { return a.Viewers() > b.Viewers(); });
	return v;

}

TwitchXX::TwitchFeaturedStreamsContainer TwitchXX::TwitchStreams::GetFeaturedStreams() const
{
	web::uri_builder builder(U("/streams/featured"));
	builder.append_query(U("limit"), 100);
	TwitchContainer<TwitchFeaturedStream> chunk;
	for(;;)
	{
		auto value = (*_request)(builder.to_uri());
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
		if(!next.is_null() && next.is_string())
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
	auto value = (*_request)(builder.to_uri());
	if (value.is_null())
	{
		throw std::runtime_error("Can not get streams summary!");
	}

	auto viewers = value.at(U("viewers")).as_number().to_uint32();
	auto channels = value.at(U("channels")).as_number().to_uint32();

	return std::make_tuple(viewers, channels);
}

TwitchXX::TwitchStreamsContainer TwitchXX::TwitchStreams::GetFollowedStreams(TwitchStream::Type type)
{
	_limit = max_limit;
	_offset = 0;
	TwitchStreamsContainer result;
	web::uri_builder builder(U("/streams/followed"));
	builder.append_query(U("limit"), max_limit); //TODO: Check perfomance if limit is equal to actual number of channel followd (if < 100)
	if(type != TwitchStream::Type::none)
	{
		builder.append_query(U("stream_type"), type_to_string(type));
	}
	for(;;)
	{
		TwitchStreamsContainer chunk;
		auto value = (*_request)(builder.to_uri());
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
		if (!next.is_null() && next.is_string())
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

web::uri_builder TwitchXX::TwitchStreams::GetBuilder(const std::wstring& url, const options& op)
{
	web::uri_builder builder(url);
	for (const auto& option : op)
	{
		builder.append_query(option.first, option.second);
	}

	return builder;
}
web::uri_builder TwitchXX::TwitchStreams::GetBuilder(const std::wstring& url, const options& op, size_t offset, size_t limit) const
{
	options options{ op };
	auto it = options.find(U("offset"));
	if (it != options.end()) options.erase(it);
	it = options.find(U("limit"));
	if (it != options.end()) options.erase(it);
	auto builder = GetBuilder(url, options);
	builder.append_query(U("offset"), offset);
	builder.append_query(U("limit"), limit);
	return builder;
}


template<>
TwitchXX::TwitchStream TwitchXX::Create(const web::json::value& obj) 
{
	TwitchStream stream;
	if (obj.is_null())
	{
		stream.Offline(true);
		return stream;
	}

	JsonWrapper wrapper (obj);

	stream.Game(*wrapper[U("game")]);
	stream.Viewers(*wrapper[U("viewers")]);
	stream.AvgFps(*wrapper[U("average_fps")]);
	stream.Delay(*wrapper[U("delay")]);
	stream.VideoHeight(*wrapper[U("video_height")]);
	stream.IsPlaylist(*wrapper[U("is_playlist")]);
	stream.Created(*wrapper[U("created_at")]);
	stream.Id(*wrapper[U("_id")]);
	stream.Channel(Create<TwitchChannel>(obj.at(U("channel"))));
	stream.Preview(CreateCollection(obj.at(U("preview"))));

	return stream;
}

template <>
TwitchXX::TwitchFeaturedStream TwitchXX::Create<TwitchXX::TwitchFeaturedStream>(const web::json::value& obj)
{
	TwitchFeaturedStream stream;
	JsonWrapper wrapper(obj);

	stream.Image(*wrapper[U("image")]);
	stream.Text(*wrapper[U("text")]);
	stream.Title(*wrapper[U("title")]);
	stream.Sponsored(*wrapper[U("sponsored")]);
	stream.Scheduled(*wrapper[U("scheduled")]);
	stream.Stream(Create<TwitchStream>(obj.at(U("stream"))));

	return stream;
}
