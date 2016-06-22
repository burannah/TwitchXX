#pragma once
#include <stdexcept>
#include <cpprest/http_msg.h>

namespace TwitchXX
{
	class TwitchException : public std::runtime_error
	{
	public:
		using status_code = web::http::status_code;
		explicit TwitchException(const std::string& _Message, status_code code)
			: runtime_error(_Message),
			_code(code)
		{
		}

		explicit TwitchException(const char* _Message)
			: runtime_error(_Message), _code(0)
		{
		}

		char const* what() const override
		{
			return (runtime_error::what() + std::string(" Status code: ") + std::to_string(_code)).c_str();
		};
		~TwitchException() override {};
	private:
		web::http::status_code _code;

	};

}