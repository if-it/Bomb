#pragma once
#include "Draw.h"
class Item :
	public Draw
{
public:
	Item();
	~Item();

	void Init(const Vector2& pos, const int& stage, const int& x, const int& y, const std::string& NameTag);
	void Update();
	bool Coll(int& get_Item);
	void Draw(const Vector2& sc, const Vector2& shake, const int& tex);

	struct Save_Data
	{
		int stage;
		int map_num_X;
		int map_num_Y;
	};

	Save_Data save_Data;
};

