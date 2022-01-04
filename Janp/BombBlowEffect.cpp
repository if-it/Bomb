#include "BombBlowEffect.h"

BombBlowEffect::BombBlowEffect()
{
}

BombBlowEffect::~BombBlowEffect()
{
}

void BombBlowEffect::Init(const Vector2& pos)
{
	game_object = GameObject();
	game_object.SetPos(pos);
}

void BombBlowEffect::Update()
{
	game_object.game.pal -= 3.0f;
	if (game_object.game.pal <= 0)
	{
		game_object.game.dis = false;
	}
}

void BombBlowEffect::Draw(const Vector2& sc, const Vector2& shake, const int& tex)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
	DrawTex(game_object, tex, true, shake, sc);
}
