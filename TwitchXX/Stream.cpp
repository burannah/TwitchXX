//
// Created by buran on 23/02/18.
//

#include <Stream.h>
#include <TwitchException.h>
#include <MakeRequest.h>
#include <JsonWrapper.h>

std::string TwitchXX::StreamType::toString(TwitchXX::StreamType::Value v)
{
    switch (v)
    {
        case Value::ALL: return "all";
        case Value::LIVE: return "live";
        case Value::VODCAST: return "vodcast";
        case Value::RERUN: return "rerun";
        default: throw TwitchXX::TwitchException("Unsupported stream type!");
    }
}

TwitchXX::StreamType::Value TwitchXX::StreamType::fromString(const std::string s)
{
    if(s == "all") return Value::ALL;
    if(s == "live") return Value::LIVE;
    if(s == "vodcast") return Value::VODCAST;
    if(s == "rerun") return Value::RERUN;

    throw TwitchXX::TwitchException("Unsupported stream type!");
}

TwitchXX::StreamType::Value TwitchXX::StreamType::fromInt(int i)
{
    switch (i)
    {
        case 0: return Value::ALL;
        case 1: return Value::LIVE;
        case 2: return Value::VODCAST;
        case 3: return Value::RERUN;
        default: throw TwitchXX::TwitchException("Unsupported stream type!");
    }
}

std::tuple<std::vector<TwitchXX::Stream>, std::string>
TwitchXX::getStreams(size_t count, const char *cursor)
{
    GetStreamsOptions opt;
    opt.first = count > 100 || count == 0 ? 20 : count;
    if(cursor)
    {
        opt.after = std::string(cursor);
    }

    opt.type = StreamType::Value::ALL;

    return getStreams(opt);
}
template<typename T>
void addRangeOfParamsToBuilder(web::uri_builder& builder,const std::string name, std::vector<T> c)
{
    for(const auto& element: c)
    {
        builder.append_query(name, element);
    }
}

std::tuple<std::vector<TwitchXX::Stream>, std::string> TwitchXX::getStreams(const TwitchXX::GetStreamsOptions &opt)
{
    MakeRequest request(MakeRequest::getOptions());
    web::uri_builder builder("helix/streams");

    if((opt.first == 0 || opt.first > 100)
        || opt.communitIds.size() > 100
        || opt.gameIds.size() > 100
        || opt.langs.size() > 100
        || opt.userIds.size() > 100
        || opt.userLogin.size() > 100)
    {
        std::stringstream ss;
        ss << "To many request parameters: Count=" << opt.first
           << " CommunityIds=" << opt.communitIds.size()
           << " GameIds=" << opt.gameIds.size()
           << " Languages=" << opt.langs.size()
           << " UserIds=" << opt.userIds.size()
           << " UserLogin=" << opt.userLogin.size() << "\n";

        throw TwitchException(ss.str().c_str());
    }
    builder.append_query("first", opt.first);

    if (opt.after.size())
    {
        builder.append_query("after", opt.after);
    }
    else if (opt.before.size())
    {
        builder.append_query("before", opt.before);
    }

    addRangeOfParamsToBuilder(builder, "community_id", opt.communitIds);
    addRangeOfParamsToBuilder(builder, "game_id", opt.gameIds);
    addRangeOfParamsToBuilder(builder, "language", opt.langs);
    addRangeOfParamsToBuilder(builder, "language", opt.langs);

    builder.append_query("type", StreamType::toString(opt.type));

    addRangeOfParamsToBuilder(builder, "user_id", opt.userIds);
    addRangeOfParamsToBuilder(builder, "user_login", opt.userLogin);

    auto response = request.get(builder.to_uri());
    std::vector<Stream> result;

    if (response.has_field("data") && !response.at("data").is_null() && response.at("data").size())
    {
        auto data = response.at("data").as_array();

        result.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](auto &&val)
        {
            JsonWrapper w(val);
            Stream s;
            s.Id = *w["id"];
            s.UserId = *w["user_id"];
            s.GameId = *w["game_id"];

            //TODO: Support array fields in Property class
            if(val.has_field("community_ids")
               && !val.at("community_ids").is_null()
               && val.at("community_ids").size())
            {
                auto communities = val.at("community_ids").as_array();
                auto proxy = s.CommunityIds.Get(); //I'm too lazy to specify the type
                std::for_each(communities.begin(), communities.end(), [&](auto&& c)
                {
                    proxy.push_back(c.as_string());
                });
                s.CommunityIds = proxy;
            }

            s.Type = StreamType::fromString(*w["type"]);
            s.Title = *w["title"];
            s.Viewers = *w["viewer_count"];
            s.Started = DateFromString(*w["started_at"]);
            s.Language = *w["language"];
            s.Thumb = *w["thumbnail_url"];

            result.push_back(s);
        });
    }

    std::string new_cursor;
    try
    {
        new_cursor = response.at("pagination").at("cursor").as_string();
    }
    catch(web::json::json_exception& e)
    {
        new_cursor = "Error cursor!";
    }

    return std::make_tuple(result, new_cursor);
}
