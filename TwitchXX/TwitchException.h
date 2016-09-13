#pragma once
#include <stdexcept>
#include <cpprest/http_msg.h>

namespace TwitchXX
{
	///Base Twitch exception class
	class TwitchException : public std::runtime_error
	{
	public:
		///Status code alias from cpprestsdk (Casablanka)
		using status_code = web::http::status_code;
		///Exception constructor with status code
		///@param _Message exception message
		///@param code status code if any
		explicit TwitchException(const std::string& _Message, status_code code)
			: runtime_error(_Message),
			_code(code)
		{
			_msg = runtime_error::what() + std::string(". Status code: ") + std::to_string(_code);
		}

		///Simple exception constructor
		///@param _Message exception message
		explicit TwitchException(const char* _Message)
			: TwitchException{_Message,0}
		{
		}

		///Exception message
		///@return exception description as a string
		const char* what() const noexcept override
		{

			return _msg.c_str();
		}

		web::http::status_code code() const { return _code; }
	private:
		web::http::status_code _code;
		std::string _msg;

	};
}