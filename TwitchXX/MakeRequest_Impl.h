//
// Created by buran on 17/04/18.
//

#ifndef TWITCHXX_MAKEREQUEST_IMPL_H
#define TWITCHXX_MAKEREQUEST_IMPL_H

#include <cpprest/json.h>

namespace TwitchXX
{

    class RequestParams;
    class RequestParams;
    class MakeRequest_Impl
    {
        public:
            ///MakeRequest's main method.
            ///@param	params request parameters descriptor
            ///@return	response parsed to web::json::value object. Null json value if HTTP result code != OK.
            virtual web::json::value performRequest(const RequestParams &params);
    };
}


#endif //TWITCHXX_MAKEREQUEST_IMPL_H
