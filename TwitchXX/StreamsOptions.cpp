//
// Created by buran on 03/03/18.
//

#include <StreamsOptions.h>
#include <TwitchException.h>
#include "MakeRequest.h"

void TwitchXX::StreamsOptions::validate(const TwitchXX::StreamsOptions& opt)
{
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
}

void TwitchXX::StreamsOptions::fillBuilder(web::uri_builder &builder, const TwitchXX::StreamsOptions &opt)
{
    validate(opt);

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

    if(opt.type != StreamType::Value::NONE)
    {
        builder.append_query("type", StreamType::toString(opt.type));
    }

    addRangeOfParamsToBuilder(builder, "user_id", opt.userIds);
    addRangeOfParamsToBuilder(builder, "user_login", opt.userLogin);
}





