#include "BombSpawnEffect.h"

BombSpawnEffect::BombSpawnEffect()
{
}

BombSpawnEffect::~BombSpawnEffect()
{
}

void BombSpawnEffect::Init()
{
	obj.clear();
	fle_Bomb_Num = 0;
}

void BombSpawnEffect::Update(const Vector2& pos, const int& now_Bomb_Num)
{
	int num = 0;
	if (now_Bomb_Num < fle_Bomb_Num)
	{
		game_object.SetPos(Vector2(pos.x + 32, pos.y + 32));
		obj.push_back(game_object);
	}
	for (int i = 0; i < (int)obj.size(); ++i)
	{
		if (obj[i].game.dis)
		{
			obj[i].game.pal -= 25.0f;
			if (obj[i].game.pal <= 0)
			{
				obj[i].game.dis = false;
			}
			++num;
		}
	}
	if (num == 0)
	{
		obj.clear();
	}
	fle_Bomb_Num = now_Bomb_Num;
}

void BombSpawnEffect::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)obj.size(); ++i)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, obj[i].game.pal);
		Circle(obj[i], 15, 10, true, shake, sc);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
