#include "SkillEffectOrigin.h"

SkillEffectOrigin::SkillEffectOrigin()
{
}

SkillEffectOrigin::~SkillEffectOrigin()
{
}

void SkillEffectOrigin::Init(Vector2 ang, const Vector2& pos)
{
	game_object = GameObject();
	game_object.game.allVec.ang = ang;
	game_object.SetPos(Vector2(pos.x + 2, pos.y + 32));
	count = 0;
}

void SkillEffectOrigin::Update(const Vector2&sc)
{
	game_object.game.allVec.vec += game_object.game.allVec.ang * SKILL_EFFECT_ORIGIN_SPEED;
	game_object.game.allVec.AddPos();
	++count;
	if (count > 3)
	{
		count = 0;
		for (int i = 0; i < 30; ++i)
		{
			if (!skill_Effect[i].game_object.game.dis)
			{
				skill_Effect[i].Init(game_object.GetPos());
				break;
			}
		}
	}
	for (int i = 0; i < 30; ++i)
	{
		if (skill_Effect[i].game_object.game.dis)skill_Effect[i].Update();
	}
	if (game_object.GetPos().x < 0||game_object.GetPos().x>sc.x+ WIDTH||
		game_object.GetPos().y<0||game_object.GetPos().y>sc.y+ HEIGHT)
	{
		game_object.game.dis = false;
	}

}

void SkillEffectOrigin::Draw(const Vector2& sc, const Vector2& shake, const int& tex, const int& lightTex)
{
	DrawTex(game_object, tex, true, shake, sc);
	SetBright(COLOR(240, 250, 139));
	for (int i = 0; i < 30; ++i)
	{
		skill_Effect[i].Draw(sc, shake, lightTex);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetBright();
}
