#include "AroundEffectMana.h"

AroundEffectMana::AroundEffectMana()
{
}

AroundEffectMana::~AroundEffectMana()
{
}

void AroundEffectMana::Init()
{
	for (int i = 0; i < AROUND_NUM; ++i)
	{
		Spawen(i, 10);
	}
	game_object.color = COLOR(10, 10, 10);
}

void AroundEffectMana::Spawen(const int& num, const int& hp)
{
	around_Efe[num].Init();
	around_Efe[num].game_object.game.rota = GetRand(10) + 1;
	int size = GetRand(2) + 1;
	around_Efe[num].game_object.game.scale = Vector2(size, size);
	around_Efe[num].game_object.game.size = around_Efe[num].game_object.game.scale * SIZE;
	around_Efe[num].subPal = GetRand(5) + 3;
	float vec = (GetRand(10) + 10) / 10;

	if (hp <= 1)
	{
		vec = (GetRand(10) + 10)/4;
	}

	switch (GetRand(3))
	{
	case 0:
		around_Efe[num].game_object.SetPos(Vector2(GetRand(WIDTH), -around_Efe[num].game_object.game.size.y));
		around_Efe[num].game_object.game.allVec.vec = Vector2(0, vec);
		break;
	case 1:
		around_Efe[num].game_object.SetPos(Vector2(GetRand(WIDTH), HEIGHT + around_Efe[num].game_object.game.size.y));
		around_Efe[num].game_object.game.allVec.vec = Vector2(0, -vec);
		break;
	case 2:
		around_Efe[num].game_object.SetPos(Vector2(-around_Efe[num].game_object.game.size.x, GetRand(HEIGHT)));
		around_Efe[num].game_object.game.allVec.vec = Vector2(vec, 0);
		break;
	case 3:
		around_Efe[num].game_object.SetPos(Vector2(WIDTH + around_Efe[num].game_object.game.size.x, GetRand(HEIGHT)));
		around_Efe[num].game_object.game.allVec.vec = Vector2(-vec, 0);
		break;
	default:
		break;
	}
}

void AroundEffectMana::Loading(Load* load)
{
	load->LoadTex("Load/Texture/Effect/howa.png", tex);
}

void AroundEffectMana::Update(const int& hp)
{

	for (int i = 0; i < AROUND_NUM; ++i)
	{
		around_Efe[i].Update();
		if (!around_Efe[i].game_object.game.dis)
		{
			Spawen(i, hp);
		}
	}
}

void AroundEffectMana::Draw()
{
	SetBright(game_object.color);
	for (int i = 0; i < AROUND_NUM; ++i)
	{
		around_Efe[i].Draw(tex);
	}
	SetBright();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
