//
// Created by buran on 30/01/18.
//

#include <MakeRequest.h>
#include <Auth/AppAccessToken.h>
#include <TwitchException.h>

TwitchXX::AppAccessToken::AppAccessToken()
:_handle(std::make_shared<Handle>())
,_request(MakeRequest::getOptions())
{
    refreshToken();
}

void TwitchXX::AppAccessToken::refreshToken()
{

    auto opt = MakeRequest::getOptions();
    web::uri_builder builder("kraken/oauth2/token");
    builder.append_query("client_id",opt["api_key"]);
    builder.append_query("client_secret", opt["client_secret"]);
    builder.append_query("grant_type", "client_credentials");

    auto response = _request.post(builder.to_uri());

    _handle->_token = response.at("access_token").as_string();
    _handle->_validTill = std::chrono::system_clock::now()
                          + std::chrono::seconds(response.at("expires_in").as_integer());
    //TODO: Fix scope parsing
    //_handle->_scope = response.at("scope").as_string();
}

void TwitchXX::AppAccessToken::revoke()
{
    auto opt = MakeRequest::getOptions();
    web::uri_builder builder("kraken/oauth2/revoke");
    builder.append_query("client_id",opt["api_key"]);
    builder.append_query("token", _handle->_token);

    auto response = _request.post(builder.to_uri());

    if(response.at("status").as_string() != "ok" )
    {
        //TODO: Log?
        std::cerr << "Can not revoke token: " << response.at("status").as_string() << "\n";
    }
}
