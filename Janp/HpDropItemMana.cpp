#include "HpDropItemMana.h"

HpDropItemMana::HpDropItemMana()
{
}

HpDropItemMana::~HpDropItemMana()
{
}

void HpDropItemMana::Init()
{
	hpDropItem.clear();
}

void HpDropItemMana::Loading(Load* load)
{
	load->LoadTex("Load/Texture/Effect/HpDropItem.png", tex);
}

void HpDropItemMana::Spawn(Vector2 pos)
{
	bool des_flg = false;
	for (int i = 0; i < (int)hpDropItem.size(); ++i)
	{
		if (!hpDropItem[i].game_object.game.dis)
		{
			des_flg = true;
			hpDropItem[i].Spawn(pos);
			break;
		}
	}
	if (!des_flg)
	{
		HpDropItem InitDrop;
		InitDrop.Spawn(pos);
		hpDropItem.push_back(InitDrop);
	}
}

void HpDropItemMana::Update()
{
	for (int i = 0; i < (int)hpDropItem.size(); ++i)
	{
		hpDropItem[i].Update();
	}
	if (NowNum() == 0)
	{
		hpDropItem.clear();
	}
}


void HpDropItemMana::Coll()
{
	for (int i = 0; i < (int)hpDropItem.size(); ++i)
	{
		hpDropItem[i].Coll();
	}
}

int HpDropItemMana::NowNum()
{
	int num = 0;
	for (int i = 0; i < (int)hpDropItem.size(); ++i)
	{
		if (game_object.game.dis)
		{
			++num;
		}
	}
	return num;
}

void HpDropItemMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)hpDropItem.size(); ++i)
	{
		hpDropItem[i].Draw(sc, shake, tex);
	}
}
