#pragma once
#include <cpprest/json.h>

namespace TwitchXX
{
	///A virtual base for JsonNotNullValueWrapper and JsonNullValueWrapper
	/** An abstract interface class*/
	class JsonValueWrapper
	{
	public:
		virtual ~JsonValueWrapper()
		{
		}

		virtual utility::string_t as_string() const = 0;
		virtual int as_integer() const = 0;
		virtual bool as_bool() const = 0;
		virtual double as_double() const = 0;
		virtual web::json::number as_number() const = 0;
		virtual unsigned int as_uint() const = 0;
		virtual unsigned long long as_ulong() const { return 0; }


		virtual operator std::wstring() const { return as_string(); };
		virtual operator int() const { return as_integer(); };
		virtual operator bool() const { return as_bool(); };
		virtual operator double() const { return as_double(); }
		virtual operator web::json::number() const { return as_number();}
		virtual operator unsigned int() const { return as_uint(); }
		virtual operator unsigned long long() const { return as_ulong(); }


	};
	//A web::json::value objects
	/**
	* A class representin an actual web::json::value object.
	*/
	class JsonNotNullValueWrapper : public JsonValueWrapper
	{
	public:
		///Wrapping up web::json::value object
		explicit JsonNotNullValueWrapper(const web::json::value& value) : _json(value) {};
		///Must always wrap some existing object
		JsonNotNullValueWrapper() = delete;


		///@{
		/** Basic type getters for stub-object.
		* These methods dosen't get the actual value type of underlying, so it's still can throw. (It's intentional. To prevent implicit type conversions e.t.c).
		*/
		utility::string_t as_string() const override
		{ return _json.as_string(); }

		int as_integer() const override
		{ return _json.as_integer(); }

		bool as_bool() const override
		{ return _json.as_bool(); }

		double as_double() const override
		{ return  _json.as_double(); }

		web::json::number as_number() const override
		{ return  _json.as_number(); }

		unsigned int as_uint() const override
		{ return _json.is_string() ? std::stoul(_json.as_string()) : _json.as_number().to_uint32();	}

		unsigned long long as_ulong() const override
		{ return _json.is_string()? std::stoll(_json.as_string()) : _json.as_number().to_uint64(); }
		///@}

	private:
		web::json::value _json;
	};

	/// web::json::value wrapper for non-existing elements.
	/**
	* Used as a stub, to get a default value of any requested type, if such element is not present in some object wrapped by JsonWrapper class object.
	*/
	class JsonNullValueWrapper: public JsonValueWrapper
	{
	public:
		utility::string_t as_string() const override { return utility::string_t(); };
		int as_integer() const override { return 0; };
		bool as_bool() const override { return false; }
		double as_double() const override { return 0; };
		web::json::number as_number() const override { return web::json::value(0).as_number(); };
		unsigned int as_uint() const override { return 0; }
		unsigned long long as_ulong() const override { return 0; }
	};

	/// web::json::value::object wrapper class
	/** 
	* Can be used to wrap up web::json::value::object objects to access thier elemets without a chance to get an exception, 
	* if there is no such request element present. If key is present it returns its value, or default value otherwise.
	*/
	class JsonWrapper
	{
	public:
		///Constructor.
		explicit JsonWrapper(const web::json::value& value) : _json(value) {}
		///Cannot be empty, must wrap some json object.
		JsonWrapper() = delete; 

		/// Accessing the values of keys
		/** If key exist for current json object returns JsonNotNullValueWrapper object, and if it does not - JsonNullVAlueWrapper one.*/
		std::unique_ptr<JsonValueWrapper> operator[] (const std::wstring& param)
		{
			if (param_exist(param)) 
				return std::make_unique<JsonNotNullValueWrapper>(_json[param]); 
			return std::make_unique<JsonNullValueWrapper>();
		}

	private:
		web::json::value _json;

		bool param_exist(const std::wstring & param) { return _json.has_field(param) && !_json[param].is_null(); };
	};
	
}
