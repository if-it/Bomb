#include "RockAttackMana.h"

RockAttackMana::RockAttackMana()
{
}

RockAttackMana::~RockAttackMana()
{
}

void RockAttackMana::Init()
{
	rock_Attack.clear();
}

void RockAttackMana::Loading(Load* load)
{
	load->LoadTex("Load/Texture/Enemy/Enemy2/RockAttack.png", tex);
}

void RockAttackMana::Update()
{
	int now_Num = 0;
	for (int i = 0; i < (int)rock_Attack.size(); ++i)
	{
		if (rock_Attack[i].game_object.game.dis)
		{
			rock_Attack[i].Update();
			++now_Num;
		}
	}
	if (now_Num == 0)
	{
		rock_Attack.clear();
	}
}

void RockAttackMana::Spawn(const int num, const Vector2& sc)
{
	for (int i = 0; i < num; ++i)
	{
		RockAttack InitRockAttack;
		Vector2 pos = Vector2();
		pos.x = GetRand(WIDTH - sc.x);
		pos.y =   sc.y - SIZE-GetRand(50);
		InitRockAttack.Init(pos);
		rock_Attack.push_back(InitRockAttack);
	}
}

void RockAttackMana::Coll()
{
	for (int i = 0; i < (int)rock_Attack.size(); ++i)
	{
		rock_Attack[i].Coll();
	}
}

void RockAttackMana::Delete_Rock()
{
	rock_Attack.clear();
}

void RockAttackMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)rock_Attack.size(); ++i)
	{
		rock_Attack[i].Draw(sc, shake, tex);
	}
}
