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
	load->LoadAnimeTex("Load/Texture/Ex/ExTex16.png", 12, 12, 1, SIZE, SIZE, exTex);
	load->LoadTex("Load/Texture/Box.png", boxTex);
	load->LoadSound("Load/Sound/SE/Explosion01.wav", exSound);
}

void ExplosionMana::Update()
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Update();
	}
	if (NowExNum() == 0)
	{
		ex.clear();
	}
}

void ExplosionMana::ExSpawn(GameObject& go , const int& damage)
{

	Explosion InitEx;
	InitEx.Init();
	InitEx.game_object.game.dis = true;
	InitEx.game_object.game.allVec.pos = go.game.allVec.pos;
	InitEx.game_object.game.allVec.pos -= SIZE / 2;
	InitEx.damage = damage;
	InitEx.game_object.game.num = (int)ex.size();
	InitEx.dis2 = true;
	PlaySoundMem(exSound, DX_PLAYTYPE_BACK, true);
	//InitEx.game_object.allVec.pos -= SIZE / 2;
	ex.push_back(InitEx);
}

void ExplosionMana::Map_Coll_Update(std::vector<std::vector<int>>& collMap, BlockParticleMana* blockParticleMana)
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Map_Coll_Update(collMap, blockParticleMana);
	}
}

void ExplosionMana::Coll(Collision* coll, ALLVECTOR all, Vector2 size)
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Coll(coll, all, size);
	}
}

void ExplosionMana::Se_Volume(int volume)
{
	ChangeVolumeSoundMem(volume, exSound);
}

void ExplosionMana::Draw(const Vector2& sc, const Vector2& shakeconst)
{
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		ex[i].Draw(sc, shakeconst, exTex,boxTex);
	}
}

int ExplosionMana::NowExNum()
{
	int nuwNum = 0;
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		if (ex[i].game_object.game.dis||ex[i].dis2)++nuwNum;
	}
	return nuwNum;
}
