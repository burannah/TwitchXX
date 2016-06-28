#pragma once
#include "TwitchDef.h"
#include "MakeRequest.h"

namespace TwitchXX
{
	const int max_limit = 100;
	class TwithcGame;
	class TwitchStream;

	extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;

	///Base template class for other twitch request classes
	template<typename T>
	class TwitchRequest
	{
	public:
		///Constructor
		///@param request transport object
		///@param limit (deprecated) maximum number of objects per physical request. [Do not rely on this!]
		explicit TwitchRequest(std::shared_ptr<MakeRequest> request, int limit = 25) 
			: _total_size(0),
			_offset(0),
			_limit(limit),
			_request(request)
		{

		}

	protected:
		TwitchContainer<T> _objects;
		size_t _total_size;
		size_t _offset;
		size_t _limit;

		std::shared_ptr<MakeRequest> _request;

		///Fetch chunk of objects of type T
		///@param uri request parameters
		///@param root_node json node containg an array of json objects of type T
		///@param update_total update total number of objects per request.
		///@return collection of objects of type T
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

		///Update total numer of objects of type T available on Twitch
		///(Deprecated)
		///@param response json object from twitch resposne
		void UpdateTotalObjectsNumber(const web::json::value& response)
		{
			auto total = response.at(U("_total"));
			if (total.is_null() || !total.is_number()) return;
			auto new_total = total.as_integer();
#ifdef _DEBUG
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

	///Template function for creating Twitch objects from JSON
	/** Default template is a stub, that throws std::runtime_error */
	template<typename T>
	T Create(const web::json::value& json)
	{
		throw std::runtime_error("Unknonw requet type!");
	}
}
