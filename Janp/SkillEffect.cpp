#include "SkillEffect.h"

SkillEffect::SkillEffect()
{
	game_object = GameObject("", false);
}

SkillEffect::~SkillEffect()
{
}

void SkillEffect::Init(const Vector2& pos)
{
	game_object = GameObject();
	game_object.SetPos(Vector2(pos.x + 16, pos.y + 16));
	sizeUp = true;
	sizeVec = Vector2();
}

void SkillEffect::Update()
{
	game_object.game.pal -= 5;
	if (game_object.game.pal < 0)
	{
		game_object.game.dis = false;
	}

}

void SkillEffect::Draw(const Vector2& sc, const Vector2& shake, const int& tex)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
	DrawTex(game_object, tex, true, shake, sc);
}
