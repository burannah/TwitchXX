#pragma once
#include <cpprest/json.h>
#include <map>

namespace TwitchXX
{
	class TwitchGame
	{
	public:
		using ImageCollection = std::map<std::wstring, std::wstring>;

		TwitchGame();
		explicit TwitchGame(web::json::value json);
		virtual ~TwitchGame();

		//void Name(const std::string& name) { _name = name; }
		std::wstring Name() const { return _name; }

		//void Channels(int count) { _channels = count; }
		unsigned int Channels() const { return _channels; }

		//void Viewers(int count) { _viewers = count; }
		unsigned int Viewers() const { return _viewers; }

		//void Id(int id) { _id = id; }
		unsigned intId() const { return _id; }

		//void Giantbomb_Id(int id) { _giantbomb_id = id; }
		unsigned int Giantbomb_Id() const { return _giantbomb_id; }

		//void Box(const ImageCollection& col) { _box = col; }
		const ImageCollection& Box() const { return _box; }

		//void Logo(const ImageCollection& col) { _logo = col; }
		const ImageCollection& Logo() const { return _logo; }

	private:
		std::wstring _name;
		unsigned int _channels;
		unsigned int _viewers;
		unsigned int _id;
		unsigned int _giantbomb_id;
		ImageCollection _box;
		ImageCollection _logo;

		static void FillCollection(ImageCollection& col, const web::json::value& json);
	};
}

