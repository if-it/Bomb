#include "AroundEffect.h"

AroundEffect::AroundEffect()
{
}

AroundEffect::~AroundEffect()
{
}

void AroundEffect::Init()
{
	game_object = GameObject();
	rota = 0.0f;
	subPal = 0;
}

void AroundEffect::Update()
{
	if (game_object.game.dis)
	{
		game_object.game.allVec.AddPos();
		game_object.game.rota += rota;
		game_object.game.pal -= subPal;
		if (game_object.game.pal <= 0)
		{
			game_object.game.dis = false;
		}
	}
}

void AroundEffect::Draw(const int& tex)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
	DrawRotaTex(game_object, tex);
}
