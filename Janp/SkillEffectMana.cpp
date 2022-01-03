#include "SkillEffectMana.h"

SkillEffectMana::SkillEffectMana()
{
}

SkillEffectMana::~SkillEffectMana()
{
}

void SkillEffectMana::Init(const Vector2& pos)
{
	Vector2 ang[8] = { Vector2(0,1),Vector2(0.5f,0.5f),Vector2(1,0),Vector2(0.5f,-0.5f),Vector2(0,-1),Vector2(-0.5f,-0.5f),Vector2(-1,0),Vector2(-0.5f,0.5f) };
	for (int i = 0; i < 8; ++i)
	{
		skill_Effect_Origin[i].Init(ang[i], pos);
	}
	ani = Animation();
	skill_End = false;
}

void SkillEffectMana::Loading(int* itemtex, int& duat)
{
	tex = itemtex;
	lightTex = duat;
}

void SkillEffectMana::Update(const Vector2& sc)
{
	int num = 0;
	ani.Round_Trip_Animation(1, 5);
	for (int i = 0; i < 8;++i)
	{
		skill_Effect_Origin[i].Update(sc);
		if (skill_Effect_Origin[i].game_object.game.dis)
		{
			++num;
		}
	}
	if (num == 0)
	{
		skill_End = true;
	}
}

void SkillEffectMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < 8; ++i)
	{
		skill_Effect_Origin[i].Draw(sc, shake, tex[ani.num], lightTex);
	}
}
