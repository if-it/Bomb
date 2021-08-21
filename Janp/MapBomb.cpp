#include "MapBomb.h"

MapBomb::MapBomb()
{
}

MapBomb::~MapBomb()
{
}

void MapBomb::Init(const Vector2& pos)
{
	game_object = GameObject("MapBomb");
	game_object.SetPos(pos);
	bomb_count = Count();
	exSpawn = false;
}


void MapBomb::Update(const bool& switch_on)
{
	bomb_count.Conuter(60 * 3);

	if (!switch_on)
	{
		ani.num = 4;
	}
	else if (!bomb_count.flg)
	{
		ani.AnimationOn(10, 4);
	}
}

void MapBomb::Coll(bool& shakeflg, Controller* con, const bool& switch_on)
{
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "Player" && switch_on && !bomb_count.flg)
		{
			shakeflg = true;
			bomb_count.flg = true;
			exSpawn = true;
			con->Shake(1000, 300);
			ani.num = 4;
		}
	}
}

void MapBomb::Coll_End_Set(ExplosionMana* ex)
{
	if (exSpawn)
	{
		exSpawn = false;
		ex->ExSpawn(game_object, 1);
	}
}

void MapBomb::Draw(const Vector2& sc, const Vector2& shake, int* tex)
{
	DrawTex(game_object, tex[ani.num], true, shake, sc);
}
