#include "ChannelFeedTest.h"
#include <TwitchDef.h>


TEST_F(ChannelFeedTest,GetPosts1)
{
	TwitchXX::TwitchPostsContainer posts;
	EXPECT_NO_THROW(
	{
		posts = _api->GetPosts(U("bangbangalang"),1);
	});

	ASSERT_EQ(posts.size(), 1);
	auto post = *(posts.begin());
	EXPECT_EQ(post.Id, 1044472381464051179);
	EXPECT_EQ(post.Created.Get(), TwitchXX::DateFromString(U("2016-05-24T00:52:59Z")));
	EXPECT_EQ(post.Created.to_string(), U("2016-05-24T00:52:59Z"));
	EXPECT_FALSE(post.Deleted);
	EXPECT_EQ(post.Endorsed_Count, 0);
	EXPECT_EQ(post.Endorsed_Users.size(), 0);
	EXPECT_EQ(post.Body.Get(), U("this work?"));
	
	auto user = post.Author;
	EXPECT_EQ(user.Display_Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Id, 104447238);
	EXPECT_EQ(user.Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Type.Get(), U("user"));
	EXPECT_EQ(user.Bio.Get(), U("i like turtles and cats"));
	EXPECT_EQ(user.Created.Get(), TwitchXX::DateFromString(U("2015-10-15T19:52:17Z")));
	EXPECT_EQ(user.Created.to_string(), U("2015-10-15T19:52:17Z"));
	EXPECT_EQ(user.Updated.Get(), TwitchXX::DateFromString(U("2016-06-21T06:01:05Z")));
	EXPECT_EQ(user.Updated.to_string(), U("2016-06-21T06:01:05Z"));
	EXPECT_EQ(user.Logo.Get(), U(""));
}

TEST_F(ChannelFeedTest, GetPosts100)
{
	TwitchXX::TwitchPostsContainer posts;
	EXPECT_NO_THROW(
	{
		posts = _api->GetPosts(U("bangbangalang"));
	});

	ASSERT_EQ(posts.size(),1);
	auto post = *(posts.begin());
	EXPECT_EQ(post.Id, 1044472381464051179);
	EXPECT_EQ(post.Created.Get(), TwitchXX::DateFromString(U("2016-05-24T00:52:59Z")));
	EXPECT_EQ(post.Created.to_string(), U("2016-05-24T00:52:59Z"));
	EXPECT_FALSE(post.Deleted);
	EXPECT_EQ(post.Endorsed_Count, 0);
	EXPECT_EQ(post.Endorsed_Users.size(), 0);
	EXPECT_EQ(post.Body.Get(), U("this work?"));

	auto user = post.Author;
	EXPECT_EQ(user.Display_Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Id, 104447238);
	EXPECT_EQ(user.Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Type.Get(), U("user"));
	EXPECT_EQ(user.Bio.Get(), U("i like turtles and cats"));
	EXPECT_EQ(user.Created.Get(), TwitchXX::DateFromString(U("2015-10-15T19:52:17Z")));
	EXPECT_EQ(user.Created.to_string(), U("2015-10-15T19:52:17Z"));
	EXPECT_EQ(user.Updated.Get(), TwitchXX::DateFromString(U("2016-06-21T06:01:05Z")));
	EXPECT_EQ(user.Updated.to_string(), U("2016-06-21T06:01:05Z"));
	EXPECT_EQ(user.Logo.Get(), U(""));
}

TEST_F(ChannelFeedTest,GetPostById)
{
	TwitchXX::TwitchPost post;
	ASSERT_NO_THROW(
	{
		post = _api->GetPost(U("bangbangalang"),1044472381464051179);
	});

	EXPECT_EQ(post.Id, 1044472381464051179);
	EXPECT_EQ(post.Created.Get(), TwitchXX::DateFromString(U("2016-05-24T00:52:59Z")));
	EXPECT_EQ(post.Created.to_string(), U("2016-05-24T00:52:59Z"));
	EXPECT_FALSE(post.Deleted);
	EXPECT_EQ(post.Endorsed_Count, 0);
	EXPECT_EQ(post.Endorsed_Users.size(), 0);
	EXPECT_EQ(post.Body.Get(), U("this work?"));

	auto user = post.Author;
	EXPECT_EQ(user.Display_Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Id, 104447238);
	EXPECT_EQ(user.Name.Get(), U("bangbangalang"));
	EXPECT_EQ(user.Type.Get(), U("user"));
	EXPECT_EQ(user.Bio.Get(), U("i like turtles and cats"));
	EXPECT_EQ(user.Created.Get(), TwitchXX::DateFromString(U("2015-10-15T19:52:17Z")));
	EXPECT_EQ(user.Created.to_string(), U("2015-10-15T19:52:17Z"));
	EXPECT_EQ(user.Updated.Get(), TwitchXX::DateFromString(U("2016-06-21T06:01:05Z")));
	EXPECT_EQ(user.Updated.to_string(), U("2016-06-21T06:01:05Z"));
	EXPECT_EQ(user.Logo.Get(), U(""));
}

TEST_F(ChannelFeedTest, CreateDeletePost)
{
	TwitchXX::TwitchPost post;
	utility::string_t post_body(U("kappa"));

	ASSERT_NO_THROW(
	{
		post = _api->Post(_channel_name,post_body,false);
	});

	EXPECT_GT(post.Id, 0);
	EXPECT_LT(post.Created.Get(), std::chrono::system_clock::now());
	EXPECT_FALSE(post.Deleted);
	EXPECT_EQ(post.Endorsed_Count, 0);
	EXPECT_EQ(post.Endorsed_Users.size(), 0);
	EXPECT_EQ(post.Body.Get(), post_body);

	auto result = false;
	ASSERT_NO_THROW(
	{
		result = _api->DeletePost(_channel_name,post.Id);
	});

	EXPECT_TRUE(result);
}

TEST_F(ChannelFeedTest, AddDeleteReaction)
{
	TwitchXX::TwitchPost post;
	utility::string_t post_body(U("kappa"));

	ASSERT_NO_THROW(
	{
		post = _api->Post(_channel_name,post_body,false);
	});

	EXPECT_EQ(post.Endorsed_Count, 0);
	EXPECT_EQ(post.Endorsed_Users.size(), 0);

	bool result = false;
	ASSERT_NO_THROW(
	{
		result = _api->AddReaction(_channel_name,post.Id,0);
	});

	EXPECT_TRUE(result);

	ASSERT_NO_THROW(
	{
		post = _api->GetPost(_channel_name,post.Id);
	});

	EXPECT_EQ(post.Endorsed_Count, 1);
	EXPECT_EQ(post.Endorsed_Users.size(), 1);

	ASSERT_NO_THROW(
	{
		result = _api->RemoveReaction(_channel_name,post.Id,0);
	});

	EXPECT_TRUE(result);

	ASSERT_NO_THROW(
	{
		result = _api->DeletePost(_channel_name,post.Id);
	});

	EXPECT_TRUE(result);
}