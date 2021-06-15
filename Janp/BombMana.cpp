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

void BombMana::Loading(const int& bombSoundC, const int* bombTexC)
{
	bombSound = bombSoundC;
	for (int i = 0; i < BOMBTEX; ++i)
	{
		bombTex[i] = bombTexC[i];
	}
}



void BombMana::Update(bool& shakeflg, Controller* con, ExplosionMana* ex)
{
	for (int i = 0; i < (int)bomb.size(); ++i)
	{
		bomb[i].Update(shakeflg, con, ex);
	}
	if (NowBombNum() == 0)
	{
		bomb.clear();
	}
}

void BombMana::Coll(Collision* coll, ALLVECTOR& all, Vector2 size, bool& shakeflg, Controller* con, ExplosionMana* ex)
{
	for (int i = 0; i < (int)bomb.size(); ++i)
	{
		bomb[i].Coll(coll, all, size, shakeflg, con, ex);
	}
}


void BombMana::BombSpawn(const Vector2& set_pos, const Vector2& set_vec, const bool& playerSp)
{
	Bomb InitBomb;

	InitBomb.Init();
	InitBomb.game_object.dis = true;
	InitBomb.game_object.allVec.pos = set_pos;
	InitBomb.game_object.allVec.vec = set_vec;
	InitBomb.playerSpawn = playerSp;
	InitBomb.playerOneColl = playerSp;
	PlaySoundMem(bombSound, DX_PLAYTYPE_BACK, true);

	bomb.push_back(InitBomb);
}


void BombMana::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	for (int i = 0; i < (int)bomb.size(); ++i)
	{
		bomb[i].Map_Coll_Update(collMap);
	}
}

int BombMana::NowBombNum()
{
	int nowNum = 0;
	for (int i = 0; i < (int)bomb.size(); ++i)
	{
		if (bomb[i].game_object.dis)
		{
			nowNum++;
		}
	}
	return nowNum;
}

void BombMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)bomb.size(); ++i)
	{
		bomb[i].Draw(sc, shake, bombTex);
	}
}
