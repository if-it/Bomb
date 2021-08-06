#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Init(const Vector2& pos, const int& stage, const int& x, const int& y, const std::string& NameTag)
{
	game_object = GameObject(NameTag);
	game_object.SetPos(pos);
	save_Data = { stage,x,y };
}

void Item::Update()
{
}

bool Item::Coll(int& get_Item)
{
	if (get_Item == 2)
	{
		for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
		{
			std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
			if (nameTag == "Player")
			{
				game_object.game.dis = false;
				get_Item = 0;
				return true;
			}
		}
	}
	return false;
}

void Item::Draw(const Vector2& sc, const Vector2& shake, const int& tex)
{
	DrawTex(game_object, tex, true, shake, sc);
}

