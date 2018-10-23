//
// Created by buran on 30/01/18.
//

#include <Auth/AppAccessToken.h>
#include <TwitchException.h>
#include <Request.h>
#include <MakeRequest_Impl.h>

namespace
{
    const std::string AUTH_BASE_URL="https://id.twitch.tv/";
}

TwitchXX::AppAccessToken::AppAccessToken(const std::string &apiKey,
                                         const std::string &clientSecret)
:_handle{std::make_shared<Handle>()}
,_opt{{"base_url", AUTH_BASE_URL}, {"api_key", apiKey}, {"client_secret", clientSecret}}
,_request_impl{std::make_shared<MakeRequest_Impl>(_opt)}
{
    refreshToken();
}

void TwitchXX::AppAccessToken::refreshToken()
{

    auto empty = std::shared_ptr<AuthToken>{};
    RequestOnce request(_request_impl, empty);
    web::uri_builder builder("oauth2/token");
    builder.append_query("client_id",_opt["api_key"]);
    builder.append_query("client_secret", _opt["client_secret"]);
    builder.append_query("grant_type", "client_credentials");

    auto response = request.post(builder.to_uri());

    _handle->_token = response.at("access_token").as_string();
    _handle->_validTill = std::chrono::system_clock::now()
                          + std::chrono::seconds(response.at("expires_in").as_integer());
    if(response.has_field("scope")
       && !response.at("scope").is_null()
       && response.at("scope").size())
    {
        auto scopes = response.at("scope").as_array();
        for(const auto& js_scope: scopes)
        {
            auto scope = js_scope.as_string();

            if(scope == "clips_edit")
            {
                _handle->_scope |= AuthScope::CLIPS_EDIT;
            }
            else if(scope == "user_edit")
            {
                _handle->_scope |= AuthScope::USER_EDIT;
            }
            else if(scope == "user_read_email")
            {
                _handle->_scope |= AuthScope::USER_READ_EMAIL;
            }
            else
            {
                Log::Warn("Unknown auth scope!: " + scope);
            }
        }
    }

}

void TwitchXX::AppAccessToken::revoke()
{
    auto empty = std::shared_ptr<AuthToken>{};
    RequestOnce request(_request_impl, empty);
    web::uri_builder builder("oauth2/revoke");
    builder.append_query("client_id",_opt["api_key"]);
    builder.append_query("token", _handle->_token);

    auto response = request.post(builder.to_uri());

    if(request.statusCode() != web::http::status_codes::OK )
    {
        Log::Warn("Can not revoke token: " + response.at("status").as_string());
    }
}
