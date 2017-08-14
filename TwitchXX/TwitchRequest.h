#pragma once
#include "TwitchDef.h"
#include "MakeRequest.h"
#include "Property.h"

namespace TwitchXX
{
	const int max_limit = 100;
	class TwithcGame;
	class TwitchStream;

#ifdef _WIN32
    extern std::shared_ptr<std::map<std::wstring, std::wstring>> Options;
#else
    extern std::shared_ptr<std::map<std::string, std::string>> Options;
#endif


	///Template function for creating Twitch objects from JSON
	/** Default template is a stub */
	template<typename T>
	T Create(const web::json::value& json)
	{
		throw std::runtime_error("Unknonw requet type!");
	}


	///Base template class for other twitch request classes
	class TwitchRequest
	{
	public:
		///Constructor
		///@param request transport object
		explicit TwitchRequest(const MakeRequest& request)
			:_request(request)
		{

		}

		///Total number of objects for given type;
		mutable Property<size_t> TotalSize;

	protected:
		MakeRequest _request;


		///Requests a single object of type T.
		///Probably redundant
		///@param uri uri for object request
		///@return object of type T
		template<typename T>
		T GetSingleObject(const web::uri& uri) const
		{
			return Create<T>(_request.get(uri));
		}


		///Request a collection of objects of type T iterationg through _next field of the response
		///@param builder uri builder for requet
		///@param node node for object's collection in the reposbse body
		///@return TwitchContainer collection of elements of type T
		template<typename T>
		TwitchContainer<T> GetObjectsArrayByNext(const web::uri_builder& builder, const utility::string_t& node) const
		{
			TwitchContainer<T> result;
			auto current_builder = builder;

			while (true)
			{
				TwitchContainer<T> chunk;
				auto value = _request.get(current_builder.to_uri());
				auto target = value.at(node);
				if (!target.is_null() && target.is_array())
				{
                    if(!target.as_array().size())
                    {
                        break;
                    }
					for (const auto& subs : target.as_array())
					{
						chunk.insert(Create<T>(subs));
					}
				}
				else
				{
					break;
				}
				result.insert(chunk.begin(), chunk.end());

                if(!value.has_field(U("_links")))
                {
                    break;
                }

				auto next = value.at(U("_links")).at(U("next"));
				if (chunk.size() < max_limit && !next.is_null() && next.is_string())
				{
                    //Need to skip 'https://api.twitch.tv/kraken' at the beginning of the link
                    utility::string_t link_next = next.as_string();
					current_builder = web::uri_builder(link_next.erase(0U,28U));

				}
				else
				{
					break;
				}
			}

			return result;
		}


		///Request a collection of objects of type T iterationg through cursor field of the response
		///@param uri request
		///@param node node for object's collection in the response body
        ///@param limit maximum number of elements to fetch
		///@return TwitchContainer collection of elements of type T
		template<typename T>
		TwitchContainer<T> GetObjectsArrayByCursor(const utility::string_t& uri, const utility::string_t& node, size_t limit) const
		{
            web::uri_builder first_builder(uri);
            if(limit)
            {
                first_builder.append_query(U("limit"), limit);
            }
            limit = limit == 0 ? std::numeric_limits<decltype(limit)>::max() : limit;

            TwitchContainer<T> result;
			auto current_builder = first_builder;

			while (result.size() < limit)
			{
                TwitchContainer<T> chunk;
				auto value = _request.get(current_builder.to_uri());
				auto objects = value.at(node);
				if (!objects.is_null() && objects.is_array() && objects.as_array().size())
				{
					for (const auto& subs : objects.as_array())
					{
						chunk.insert(Create<T>(subs));
					}
				}
				else
				{
					break;
				}

				result.insert(chunk.begin(), chunk.end());
                if (value.has_field(U("_cursor")) && value.at(U("_cursor")).is_string() && value.at(U("_cursor")).as_string().size())
				{
                    //TODO: For some reason value can indicate that it has a cursor, but it's empty. So empty string check is needed.
                    current_builder = first_builder;
                    current_builder.append_query(U("cursor"), value.at(U("_cursor")).as_string());
				}
				else
				{
					break;
				}
			}

			return result;
		}

		///Request a collection of objects of type T with no iterations
		///@param builder uri builder for requet
		///@param root node for object's collection in the reposbse body
		///@return TwitchContainer collection of elements of type T
		template<typename T>
		TwitchContainer<T> GetObjectsArrayOnce(web::uri_builder& builder, const utility::string_t& node) const
		{
			TwitchContainer<T> result;
			auto value = _request.get(builder.to_uri());
			auto objects = value.at(node);
			if (!objects.is_null() && objects.is_array())
			{
				for (const auto& subs : objects.as_array())
				{
					result.insert(Create<T>(subs));
				}
			}
			return result;
		}
	};

	///Helper function to add query parameter to builder, only if it exist in options object
	///@param builder target builder
	///@param op options collection
	///@param option_name name of the option to add
	inline void AddOption(web::uri_builder& builder, const options& op, const utility::string_t& option_name)
	{
		auto option_it = op.find(option_name);
		if(option_it != op.end())
		{
			builder.append_query(option_name, option_it->second);
		}
	}

}
