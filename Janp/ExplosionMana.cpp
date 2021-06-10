#include "ExplosionMana.h"

ExplosionMana::ExplosionMana()
{
}

ExplosionMana::~ExplosionMana()
{
}

void ExplosionMana::Init()
{
	ex.clear();
}

void ExplosionMana::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/ExTex.png", 4, 4, 1, SIZE, SIZE, exTex);
}

void ExplosionMana::Update()
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Update();
	}
}

void ExplosionMana::Map_Coll_Update(int(*collMap)[MAPX])
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Map_Coll_Update(collMap);
	}
}

void ExplosionMana::Coll(Collision* coll, ALLVECTOR all, Vector2 size)
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Coll(coll, all, size);
	}
}

void ExplosionMana::Draw(const Vector2& sc, const Vector2& shakeconst)
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Draw(sc, shakeconst, exTex);
	}
}
