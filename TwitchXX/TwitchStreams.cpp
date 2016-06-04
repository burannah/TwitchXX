#include "TwitchStreams.h"
#include "TwitchChannels.h"
#include <cpprest/uri_builder.h>
#include "JsonWrapper.h"

namespace TwitchXX
{
	size_t TwitchStreams::_total_size = 0;
}

TwitchXX::TwitchStreams::TwitchStreams()
{
	_root_node = U("streams");
}


TwitchXX::TwitchStreams::~TwitchStreams()
{
}

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
	FetchChunk(GetBuilder(U("/streams"),op).to_uri()); return _total_size;
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
		auto chunk = FetchChunk(GetBuilder(U("/streams"), op, _offset, _limit).to_uri());
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

	stream.Game(wrapper[U("game")]->as_string());
	stream.Viewers(wrapper[U("viewers")]->as_integer());
	stream.AvgFps(wrapper[U("average_fps")]->as_double());
	stream.Delay(wrapper[U("delay")]->as_integer());
	stream.VideoHeight(wrapper[U("video_height")]->as_integer());
	stream.IsPlaylist(wrapper[U("is_playlist")]->as_bool());
	stream.Created(wrapper[U("created_at")]->as_string());
	stream.Id(wrapper[U("_id")]->as_number().to_uint32());
	stream.Channel(Create<TwitchChannel>(obj.at(U("channel"))));
	stream.Preview(CreateCollection(obj.at(U("preview"))));

	return stream;
}
