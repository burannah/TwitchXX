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
		TwitchContainer<T> GetObjectsMap(const web::uri& uri) const
		{

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
