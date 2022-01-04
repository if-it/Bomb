#include "BombBlowEffectMana.h"

BombBlowEffectMana::BombBlowEffectMana()
{
}

BombBlowEffectMana::~BombBlowEffectMana()
{
}

void BombBlowEffectMana::Init()
{
	bomb_Blow_Effect.clear();
	count = 0;
	spawn_Flg = false;
	game_object.color = COLOR(180, 180, 180);
}

void BombBlowEffectMana::Loading(int& duat)
{
	tex = duat;
}

void BombBlowEffectMana::Update(const bool& flg, const Vector2& pos)
{
	int num = 0;
	if (flg)
	{
		if (spawn_Flg)
		{
			count = count % 2;
		}
		else
		{
			spawn_Flg = true;
		}
	}

	if (spawn_Flg)
	{
		++count;
		if (count % 2 == 0)
		{
			Spawn(pos);
		}
		if (count == 60)
		{
			count = 0;
			spawn_Flg = false;
		}
	}

	for (int i = 0; i < (int)bomb_Blow_Effect.size(); ++i)
	{
		if (bomb_Blow_Effect[i].game_object.game.dis)
		{
			++num;
			bomb_Blow_Effect[i].Update();
		}
	}
	if (num == 0)
	{
		bomb_Blow_Effect.clear();
	}
}

void BombBlowEffectMana::Spawn(const Vector2& pos)
{
	BombBlowEffect bomb_Effect_Init;
	bomb_Effect_Init.Init(Vector2(pos.x + 32, pos.y + 50));
	bomb_Blow_Effect.push_back(bomb_Effect_Init);
}

void BombBlowEffectMana::Draw(const Vector2& sc, const Vector2& shake)
{
	SetBright(game_object.color);
	for (int i = 0; i < (int)bomb_Blow_Effect.size(); ++i)
	{
		bomb_Blow_Effect[i].Draw(sc, shake,tex);
	}
	SetBright();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
