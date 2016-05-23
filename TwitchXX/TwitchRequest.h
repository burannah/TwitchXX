#pragma once
#include <set>
#include "TwitchDef.h"
#include "MakeRequest.h"

namespace TwitchXX
{
	extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;
	template<typename T>
	class TwitchRequest
	{
	public:
		TwitchRequest(int limit = 25) :
			_limit(limit),
			_offset(0),
			_request(std::make_shared<MakeRequest<T>>((*Options)[U("api_key")],(*Options)[U("version")]))
		{

		}

		virtual ~TwitchRequest()
		{
		}

	protected:
		TwitchContainer<T> _objects;
		static size_t _total_size;
		size_t _requested_size;
		size_t _offset;
		size_t _limit;

		std::shared_ptr<MakeRequest<T>> _request;


		virtual web::uri_builder GetBuilder(size_t limit, size_t offset) = 0;

		TwitchContainer<T> FetchChunk(size_t limit, size_t offset)
		{
			auto value = (*_request)(GetBuilder(limit, offset).to_uri());
			if (value.is_null())
			{
				throw std::runtime_error("No objects were returned");
			}

			UpdateTotalObjectsNumber(value);

			auto top = value.at(L"top");
			TwitchContainer<T> chunk;
			if (top.is_array())
			{
				for each (auto& object_descriptor in top.as_array())
				{
					T obj = Create(object_descriptor);
					auto exisiting_object = std::find_if(_objects.begin(), _objects.end(), [&](const T& item) { return obj.Name() == item.Name(); });
					if (exisiting_object != _objects.end() && *exisiting_object != obj)
					{
						std::wcout << "Cache hit for object: " << exisiting_object->Name() << " , updating..." << std::endl;
						_objects.erase(exisiting_object);
					}
					chunk.insert(obj);
					std::wstringstream stream(L"");
					stream << "Added obj: " << obj.Name() << " Current viewers: " << obj.Viewers() << std::endl;
					Log->Log(stream.str());
				}
			}

			std::wcout << "Objects fetched: " << chunk.size() << std::endl;
			return chunk;
		}

		static void UpdateTotalObjectsNumber(const web::json::value& response)
		{
			auto total = response.at(U("_total"));
			if (total.is_null() || !total.is_number()) return;
#ifdef _DEBUG
			auto new_total = total.as_integer();
			if (new_total != _total_size)
			{
				std::wstringstream s;
				s << "Total amount of objects changed from " << _total_size << " to " << new_total << std::endl;
				Log->Log(s.str(), Logger::LogLevel::Debug);
			}
#endif //_DEBUG
			_total_size = new_total;
		};

		TwitchContainer<T> GetTopObjects(size_t n)
		{
			FetchChunk(0, 1); 	//Just to get the totoal number
			_requested_size = n;
			auto offset = 0;
			auto max_objects = n == 0 ? _total_size : n;
			const auto max_retries = 3;
			auto retries = 0;
			while (_objects.size() < max_objects)
			{
				int count = _objects.size();
				auto chunk = FetchChunk(_limit, _offset);
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
				_offset = count + static_cast<size_t>(chunk.size() * 0.6);
				_offset = std::min(_objects.size(), _offset);
				if (_offset + _limit > _total_size)
				{
					_offset = _total_size - _limit;
				}
				if (retries >= max_retries)
				{
					break;
				}
				std::wcout << "Before=" << count << " After=" << _objects.size() << " Chunk=" << chunk.size() << " Offset=" << _offset << " Total=" << _total_size << " Retries = " << retries << std::endl;
			}

			// Objects are sorted by names. We need to return mast watched of them == sorted by the number of viewers.
			// So here comes some trick
			std::vector<T> v(_objects.begin(), _objects.end());
			std::sort(v.begin(), v.end(), [](const T& a, const T& b) { return a.Viewers() > b.Viewers(); });
			return TwitchContainer<T>{ v.begin(), std::next(v.begin(), std::min(v.size(),max_objects)) };
		}

	};

}
