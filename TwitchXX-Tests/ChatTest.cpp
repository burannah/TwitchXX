#include "ChatTest.h"
#include <TwitchEmoticon.h>

TEST_F(ChatTest, GetEmoticons)
{
	TwitchXX::TwitchEmoticonsContainer result;
	ASSERT_NO_THROW(
	{
		result = _api->GetEmoticons();
	});

	EXPECT_GT(result.size(), unsigned{ 1 }); //TODO: Not sure how to test it
}

TEST_F(ChatTest,GetEmoticonSets)
{
	std::set<TwitchXX::EmoticonImage> result;
	ASSERT_NO_THROW(
	{
		result = _api->GetEmoticoneImages();
	});

	EXPECT_GT(result.size(), unsigned{ 1 });

	std::set<size_t> sets{ 469,0 };
	ASSERT_NO_THROW(
	{
		result = _api->GetEmoticoneImages(sets);
	});

	for (const auto& image : result)
	{
		ASSERT_TRUE(sets.find(image.EmoticoneSet) != sets.end());
	}
}

TEST_F(ChatTest,GetBadges)
{
	std::set<TwitchXX::ChannelBadge> result;

	ASSERT_NO_THROW(
	{
		result = _api->GetChannelBadges(_channel_name);
	});
	
	EXPECT_GE(result.size(), unsigned{ 6 });

	for (const auto& badge : result)
	{
		EXPECT_GT(badge.Type.size(), unsigned{ 0 });
		EXPECT_GT(badge.Svg.size(), unsigned{ 0 });
		EXPECT_GT(badge.Image.size(), unsigned{ 0 });
		EXPECT_GT(badge.Alpha.size(), unsigned{ 0 });
	}

}