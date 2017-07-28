//
// Created by buran on 7/28/17.
//
#include "TwitchUser.h"
#include "AuthToken.h"


std::map<TwitchXX::AuthScope, utility::string_t> TwitchXX::TwitchUser::Scopes = {
        {AuthScope::USER_READ,U("user_read")},
        {AuthScope::USER_BLOCKS_EDIT,U("user_blocks_edit")},
        {AuthScope::USER_BLOCKS_READ,U("user_blocks_read")},
        {AuthScope::USER_FOLLOWS_EDIT,U("user_follows_edit")},
        {AuthScope::CHANNEL_READ,U("channel_read")},
        {AuthScope::CHANNEL_EDITOR,U("channel_editor")},
        {AuthScope::CHANNEL_COMMERCIAL,U("channel_commercial")},
        {AuthScope::CHANNEL_STREAM,U("channel_stream")},
        {AuthScope::CHANNEL_SUBSCRIPTIONS,U("channel_subscriptions")},
        {AuthScope::USER_SUBSCRIPTIONS,U("user_subscriptions")},
        {AuthScope::CHANNEL_CHECK_SUBSCRIPTION,U("channel_check_subscription")},
        {AuthScope::CHAT_LOGIN,U("chat_login")},
        {AuthScope::CHANNEL_FEED_READ,U("channel_feed_read")},
        {AuthScope::CHANNEL_FEED_EDIT,U("channel_feed_edit")}
};

std::map<utility::string_t, TwitchXX::AuthScope> TwitchXX::TwitchUser::Rscopes = {};

