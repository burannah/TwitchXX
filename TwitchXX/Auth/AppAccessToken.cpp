//
// Created by buran on 30/01/18.
//

#include <MakeRequest.h>
#include <Auth/AppAccessToken.h>

TwitchXX::AppAccessToken::AppAccessToken()
:_handle(std::make_shared<Handle>())
{
    refreshToken();
}

void TwitchXX::AppAccessToken::refreshToken() const
{
    auto options = MakeRequest::getOptions();
    MakeRequest request(options);
    web::uri_builder builder("kraken/oauth2/token");
    builder.append_query("client_id",options["api_key"]);
    builder.append_query("client_secret", options["client_secret"]);
    builder.append_query("grant_type", "client credentials");
    if(options.find("scope") != options.end())
    {
        builder.append_query("scope", options["scope"]);
    }

    auto response = request.post(builder.to_uri());

    _handle->_token = response.at("access_token").as_string();
    _handle->_validTill = std::chrono::system_clock::now()
                          + std::chrono::seconds(response.at("expires_in").as_integer());
    //TODO: Fix scope parsing
    //_handle->_scope = response.at("scope").as_string();
}
