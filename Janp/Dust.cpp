#include "Dust.h"

Dust::Dust()
{
}

Dust::~Dust()
{
}

void Dust::Init(std::vector<std::vector<int>>& map, const int& stage)
{
	dust.clear();
	if (stage >= 300 && stage < 400)
	{
		mapX = map[0].size() * SIZE;
		mapY = map.size() * SIZE;
		for (int i = 0; i < 120; ++i)
		{
			GameObject Init_Dust;

			Init_Dust = GameObject();
			Init_Dust.game.pal = GetRand(245) + 10;
			Init_Dust.SetPos(Vector2(GetRand(mapX), GetRand(mapY)));
			dust.push_back(Init_Dust);
		}
	}
}

void Dust::Loading(Load* load)
{
	load->LoadTex("Load/Texture/Effect/boyaMaru.png", tex);
}

void Dust::Update()
{
	for (int i = 0; i < dust.size(); ++i)
	{
		dust[i].game.pal += GetRand(30) - GetRand(30);
		if (dust[i].game.pal >= 255)
		{
			dust[i].game.pal = 255;
		}
		else if (dust[i].game.pal <= 0)
		{
			dust[i].game.pal = 10;
		}
		dust[i].game.allVec.vec.y -= 0.006;
		dust[i].game.allVec.vec.x += (GetRand(10) - GetRand(10)) / 10;
		dust[i].game.allVec.AddPos();
		if (dust[i].GetPos().y <= -SIZE || dust[i].GetPos().x <= -SIZE || dust[i].GetPos().x > mapX)
		{
			dust[i].game.pal = GetRand(245) + 10;
			dust[i].game.allVec.vec = Vector2();
			dust[i].SetPos(Vector2(GetRand(mapX), mapY));
		}
	}
}

void Dust::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < dust.size(); ++i)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, dust[i].game.pal);
		DrawTex(dust[i], tex, true, Vector2(), sc);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
