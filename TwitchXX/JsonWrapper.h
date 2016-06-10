#pragma once
#include <cpprest/json.h>

namespace TwitchXX
{
	class JsonValueWrapper
	{
	public:
		//explicit JsonValueWrapper(const web::json::value& value) {};

		virtual ~JsonValueWrapper()
		{
		}

		virtual utility::string_t as_string() const = 0;
		virtual int as_integer() const = 0;
		virtual bool as_bool() const = 0;
		virtual double as_double() const = 0;
		virtual web::json::number as_number() const = 0;
		virtual unsigned int as_uint() const = 0;


		virtual operator std::wstring() const { return as_string(); };
		virtual operator int() const { return as_integer(); };
		virtual operator bool() const { return as_bool(); };
		virtual operator double() const { return as_double(); }
		virtual operator web::json::number() const { return as_number();}
		virtual operator unsigned int() const { return as_uint(); }
	};

	class JsonNotNullValueWrapper : public JsonValueWrapper
	{
	public:
		explicit JsonNotNullValueWrapper(const web::json::value& value) : _json(value) {};
		JsonNotNullValueWrapper() = delete;

		virtual ~JsonNotNullValueWrapper()
		{
		}

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
		{ return _json.as_number().is_uint32();	}

	private:
		web::json::value _json;
	};

	class JsonNullValueWrapper: public JsonValueWrapper
	{
	public:
		utility::string_t as_string() const override { return utility::string_t(); };
		int as_integer() const override { return 0; };
		bool as_bool() const override { return false; }
		double as_double() const override { return 0; };
		web::json::number as_number() const override { return web::json::value("0").as_number(); };
		unsigned int as_uint() const override { return 0; }
	};


	class JsonWrapper
	{
	public:
		explicit JsonWrapper(const web::json::value& value) : _json(value) {}
		JsonWrapper() = delete;

		bool param_exist(const std::wstring & param) { return _json.has_field(param) && !_json.at(param).is_null(); };
		std::unique_ptr<JsonValueWrapper> operator[] (const std::wstring& param)
		{
			if (param_exist(param)) 
				return std::make_unique<JsonNotNullValueWrapper>(_json.at(param)); 
			return std::make_unique<JsonNullValueWrapper>();
		}

	private:
		web::json::value _json;
	};
	
}
