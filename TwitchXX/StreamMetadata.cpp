//
// Created by buran on 03/03/18.
//

#include <Property.h>
#include <string>
#include "StreamMetadata.h"

namespace TwitchXX
{
    std::tuple<std::vector<TwitchXX::StreamMetadata>, std::string> getStreamsMetadata(size_t count, const char *cursor)
    {
        StreamsOptions opt;
        opt.first = count > 100 || count == 0 ? 20 : count;
        if(cursor)
        {
            opt.after = std::string(cursor);
        }

        opt.type = StreamType::Value::ALL;

        return getStreamsMetadata(opt);
    }

    std::tuple<std::vector<StreamMetadata>, std::string> TwitchXX::getStreamsMetadata(const StreamsOptions &opt)
    {
        return std::tuple<std::vector<StreamMetadata>, std::string>();
    }

}
