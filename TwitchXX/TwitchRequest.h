#pragma once
#include "TwitchDef.h"
#include "MakeRequest.h"
#include "Property.h"

namespace TwitchXX
{
	const int max_limit = 100;
	class TwithcGame;
	class TwitchStream;

	extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;

	//TODO:Deprecated
	///Base template class for other twitch request classes
	template<typename T>
	class TwitchRequest
	{
	public:
		///Constructor
		///@param request transport object
		explicit TwitchRequest(std::shared_ptr<MakeRequest> request) 
			:_request(request)
		{

		}

		///Total number of objects for given type;
		mutable Property<size_t> TotalSize;

	protected:
		TwitchContainer<T> _objects;
		std::shared_ptr<MakeRequest> _request;

		template<typename T>
		T GetSingleObject(const web::uri& uri) const
		{
			return Create<T>(_request->get(uri));
		}

		template<typename T>
		TwitchContainer<T> GetObjectsArray(const web::uri_builder& builder, const std::wstring& node) const
		{
			TwitchContainer<T> result;
			auto current_builder = builder;

			while (true)
			{
				TwitchContainer<T> chunk;
				auto value = _request->get(current_builder.to_uri());
				auto subscriptions = value.at(node);
				if (!subscriptions.is_null() && subscriptions.is_array())
				{
					for (const auto& subs : subscriptions.as_array())
					{
						chunk.insert(Create<T>(subs));
					}
				}
				else
				{
					break;
				}

				result.insert(chunk.begin(), chunk.end());

				auto next = value.at(U("_links")).at(U("next"));
				if (chunk.size() == max_limit && !next.is_null() && next.is_string())
				{
					current_builder = web::uri_builder(next.as_string());
				}
				else
				{
					break;
				}
			}

			return result;
		}
	};

	///Template function for creating Twitch objects from JSON
	/** Default template is a stub */
	template<typename T>
	T Create(const web::json::value& json) = delete;
/*	{
		throw std::runtime_error("Unknonw requet type!");
	}*/
}
