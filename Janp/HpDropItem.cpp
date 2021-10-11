#include "HpDropItem.h"

HpDropItem::HpDropItem()
{
}

HpDropItem::~HpDropItem()
{
}

void HpDropItem::Init()
{
	game_object = GameObject("HpDropItem", true, Vector2(16, 16));
	count = 600;
}

void HpDropItem::Spawn(Vector2 pos)
{
	if (GetRand(99) > 65)
	{
		Init();
		game_object.SetPos(pos);
	}
}

void HpDropItem::Update()
{
	game_object.game.pal = count;
	--count;
	game_object.game.rota -= 5;
	if (count == 0)
	{
		game_object.game.dis = false;
	}
}

void HpDropItem::Coll()
{
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "Player")
		{
			game_object.game.dis = false;
		}
	}
}

void HpDropItem::Draw(const Vector2& sc, const Vector2& shake, const int& HpTex)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
	DrawRotaTex(game_object, HpTex, true, shake, sc);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
