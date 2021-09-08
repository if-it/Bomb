#include "RockEffectMana.h"

RockEffectMana::RockEffectMana()
{
}

RockEffectMana::~RockEffectMana()
{
}

void RockEffectMana::Init()
{
	rock.clear();
}

void RockEffectMana::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Effect/Rock.png", 3, 3, 1, 16, 16, tex);
}

void RockEffectMana::Update()
{
	int now_Num = 0;
	for (int i = 0; i < (int)rock.size(); ++i)
	{
		if (rock[i].game_object.game.dis)
		{
			rock[i].Update();
			++now_Num;
		}
	}
	if (now_Num == 0)
	{
		rock.clear();
	}
}



void RockEffectMana::Spawn(const Vector2& pos, const int num)
{
	for (int i = 0; i < num; ++i)
	{
		RockEffect InitRock;
		InitRock.Init(pos);
		rock.push_back(InitRock);
	}
}

void RockEffectMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)rock.size(); ++i)
	{
		rock[i].Draw(sc, shake, tex);
	}
}
