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

		virtual utility::string_t as_string() = 0;
		virtual int as_integer() = 0;
		virtual bool as_bool() = 0;
		virtual double as_double() = 0;
		virtual web::json::number as_number() = 0;

	};

	class JsonNotNullValueWrapper : public JsonValueWrapper
	{
	public:
		explicit JsonNotNullValueWrapper(const web::json::value& value) : _json(value) {};
		JsonNotNullValueWrapper() = delete;

		virtual ~JsonNotNullValueWrapper()
		{
		}

		utility::string_t as_string() override
		{ return _json.as_string(); }

		int as_integer() override
		{ return _json.as_integer(); }

		bool as_bool() override
		{ return _json.as_bool(); }

		double as_double() override
		{ return  _json.as_double(); }

		web::json::number as_number() override
		{ return  _json.as_number(); }

	private:
		web::json::value _json;
	};

	class JsonNullValueWrapper: public JsonValueWrapper
	{
	public:
		utility::string_t as_string() override { return utility::string_t(); };
		int as_integer() override { return 0; };
		bool as_bool() override { return false; }
		double as_double() override { return 0; };
		web::json::number as_number() override { return web::json::value("0").as_number(); };
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
