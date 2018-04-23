#include <RequestOnce.h>

#include <stdexcept>
#include <cpprest/details/web_utilities.h>

#include <TwitchException.h>
#include <Utility.h>
#include <Log.h>
#include <StreamsOptions.h>
#include <RequestParams.h>
#include <MakeRequest_Impl.h>


namespace TwitchXX
{
    web::json::value RequestOnce::performRequest(const RequestParams &params) const
    {
        std::lock_guard<std::mutex> lock(_request->_lock);

        return _request->performRequest(params);
    }
}
