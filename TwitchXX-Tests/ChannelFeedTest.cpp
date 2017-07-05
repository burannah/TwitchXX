#include <chrono>
#include <thread>
#include "ChannelFeedTest.h"


TEST_F(ChannelFeedTest,GetPosts1)
{
	TwitchXX::TwitchPostsContainer posts;
	EXPECT_NO_THROW(
	{
		posts = _api->GetPosts(U("bangbangalang"),1);
	});

	ASSERT_EQ(posts.size(), 1);
}

TEST_F(ChannelFeedTest, GetPosts100)
{
	TwitchXX::TwitchPostsContainer posts;
	EXPECT_NO_THROW(
	{
		posts = _api->GetPosts(U("bangbangalang"), 100);
	});

	ASSERT_GE(posts.size(),2);
}

TEST_F(ChannelFeedTest,GetPostById)
{
	TwitchXX::TwitchPost post;
	ASSERT_NO_THROW(
	{
		post = _api->GetPost(U("bangbangalang"),U("7288b741-3341-49b1-b35c-ac87a7be7db6"));
	});

	EXPECT_GT(post.Id.Get().size(), 0);
}

TEST_F(ChannelFeedTest, CreateDeletePost)
{
	TwitchXX::TwitchPost post;
	utility::string_t post_body(U("kappa"));

	ASSERT_NO_THROW(
	{
		post = _api->Post(_channel_name,post_body,false);
	});

	EXPECT_GT(post.Id.Get().size(), 0);
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
    std::this_thread::sleep_for(std::chrono::duration<int64_t>(7)); //To prevent 500 error from twitch
	TwitchXX::TwitchPost post;
	utility::string_t post_body(U("kappa for reaction!"));

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