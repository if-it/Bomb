#include "BombMana.h"



BombMana::BombMana()
{

}

BombMana::~BombMana()
{

}

void BombMana::Init()
{
	bomb.clear();
}

void BombMana::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Bomb.png", 8, 8, 1, SIZE, SIZE, bombTex);
	load->LoadSound("Load/Sound/SE/Explosion01.wav", exSound);
}

void BombMana::Update(bool& shakeflg, Controller* con)
{
	for (int i = 0; i < bomb.size(); ++i)
	{
		bomb[i].Update(shakeflg, con);
	}
}

void BombMana::Coll(Collision* coll, ALLVECTOR all, Vector2 size, bool& shakeflg, Controller* con)
{
	for (int i = 0; i < bomb.size(); ++i)
	{
		bomb[i].Coll(coll, all, size,shakeflg, con, exSound);
	}
}

void BombMana::MapCollUpdate(int(*collMap)[MAPX])
{
	for (int i = 0; i < bomb.size(); ++i)
	{
		bomb[i].Map_Coll_Update(collMap);
	}
}

void BombMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < bomb.size(); ++i)
	{
		bomb[i].Draw(sc, shake, bombTex);
	}
}
