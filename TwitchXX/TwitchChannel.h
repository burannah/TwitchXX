#pragma once
namespace TwitchXX
{
	class TwitchChannel
	{
	public:
		TwitchChannel();
		virtual ~TwitchChannel();

		bool operator==(const TwitchChannel& other) const
		{
			return true;
		}
	};

}
