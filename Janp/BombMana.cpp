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
	load->LoadSound("Load/Sound/SE/shoot.wav", bombSound);

}

void BombMana::Update(bool& shakeflg, Controller* con, ExplosionMana* ex)
{
	for (int i = 0; i < bomb.size(); ++i)
	{
		bomb[i].Update(shakeflg, con, ex);
	}
}

void BombMana::Coll(Collision* coll, ALLVECTOR& all, Vector2 size, bool& shakeflg, Controller* con, ExplosionMana* ex)
{
	for (int i = 0; i < bomb.size(); ++i)
	{
		bomb[i].Coll(coll, all, size, shakeflg, con, ex);
	}
}


void BombMana::BombSpawn(const Vector2& set_pos, const Vector2& set_vec,const bool&playerSp)
{
	Bomb InitBomb;

	InitBomb.Init();
	InitBomb.game_object.dis = true;
	InitBomb.game_object.allVec.pos = set_pos;
	InitBomb.game_object.allVec.vec = set_vec;
	InitBomb.playerSpawn = playerSp;
	PlaySoundMem(bombSound, DX_PLAYTYPE_BACK, true);

	bomb.push_back(InitBomb);
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
