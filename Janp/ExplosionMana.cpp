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

void ExplosionMana::Loading(Load* load,const int&box)
{
	load->LoadAnimeTex("Load/Texture/ExTex16.png", 12, 12, 1, SIZE, SIZE, exTex);
	load->LoadSound("Load/Sound/SE/Explosion01.wav", exSound);
	boxTex = box;
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

void ExplosionMana::ExSpawn(GameObject& go)
{

	Explosion InitEx;
	InitEx.Init();
	InitEx.game_object.dis = true;
	InitEx.game_object.allVec.pos = go.allVec.pos;
	InitEx.game_object.allVec.pos -= SIZE / 2;
	PlaySoundMem(exSound, DX_PLAYTYPE_BACK, true);
	//InitEx.game_object.allVec.pos -= SIZE / 2;
	ex.push_back(InitEx);
}

void ExplosionMana::Map_Coll_Update(std::vector<std::vector<int>>& collMap)
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
		ex[i].Draw(sc, shakeconst, exTex,boxTex);
	}
}

int ExplosionMana::NowExNum()
{
	int nuwNum = 0;
	for (int i = 0; i < (int)ex.size(); ++i)
	{
		if (ex[i].game_object.dis)++nuwNum;
	}
	return nuwNum;
}
