//
// Created by buran on 23/01/18.
//

#include <Auth/AppAccessToken.h>
#include <Entitlement.h>
#include <TwitchException.h>
#include <RequestWait.h>
#include <RequestOnce.h>
#include <Api.h>
#include <Log.h>

std::string TwitchXX::Entitlement::getEntitlementTypeString(TwitchXX::Entitlement::Type t)
{
    static std::map<Type,std::string> mapping = { { Type::bulk_drops_grant, "bulk_drops_grant"} };
    if (mapping.find(t) == mapping.end())
    {
        std::stringstream str;
        str << __FUNCTION__ << ":" << __LINE__ << "Unsupported entitlement type";
        Log::Error(str.str());
        throw TwitchXX::TwitchException(str.str().c_str());
    }
    return mapping[t];
}

TwitchXX::Entitlement::Entitlement(const Api &api, const std::string &id, TwitchXX::Entitlement::Type t)
: Id(id)
, EntitlementType(t)
{
    web::uri_builder builder("helix/entitlements/upload");
    builder.append_query("manifest_id",id);
    builder.append_query("type",getEntitlementTypeString(t));

    api.reqWait().setAuthToken(std::make_shared<AppAccessToken>(api.getApiKey(),
                                                                api.getClientSecret()));

    auto response = api.reqWait().post(builder.to_uri());

    if(response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();
        const auto& first = *data.begin();
        Url = first.at("url").as_string();
    }
}
