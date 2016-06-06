#pragma once
#include "TwitchDef.h"
#include "MakeRequest.h"

namespace TwitchXX
{
	const int max_limit = 100;
	class TwithcGame;
	class TwitchStream;

	extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;
	template<typename T>
	class TwitchRequest
	{
	public:
		explicit TwitchRequest(int limit = 25) :
			_offset(0),
			_limit(limit),
			_request(std::make_shared<MakeRequest>((*Options)[U("version")],(*Options)[U("api_key")]))
		{

		}

		virtual ~TwitchRequest()
		{
		}

	protected:
		TwitchContainer<T> _objects;
		static size_t _total_size;
		size_t _offset;
		size_t _limit;

		std::shared_ptr<MakeRequest> _request;


		TwitchContainer<T> FetchChunk(const web::uri& uri, const std::wstring& root_node, bool update_total = true)
		{
			auto value = (*_request)(uri);
			if (value.is_null())
			{
				throw std::runtime_error("No objects were returned");
			}

			if(update_total)
			{
				UpdateTotalObjectsNumber(value);
			}
			

			auto top = value.at(root_node);
			TwitchContainer<T> chunk;
			if (top.is_array())
			{

				for each (auto& object_descriptor in top.as_array())
				{
					chunk.insert(Create<T>(object_descriptor));
				}
			}
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

	};

	template<typename T>
	T Create(const web::json::value& json)
	{
		throw std::runtime_error("Unknonw requet type!");
	}
}
