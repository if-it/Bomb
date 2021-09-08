#include "RockEffect.h"

RockEffect::RockEffect()
{
}

RockEffect::~RockEffect()
{
}

void RockEffect::Init(const Vector2& pos)
{
	game_object = GameObject("",true,Vector2(16.0f,16.0f));
	game_object.SetPos(pos);
	game_object.game.allVec.vec.x = GetRand(5) - GetRand(5);
	game_object.game.allVec.vec.y = -(GetRand(8) + 1);
	rota = GetRand(20) - GetRand(20);
	texNum = GetRand(2);
}

void RockEffect::Update()
{
	game_object.game.rota += rota;
	game_object.game.allVec.vec.y += 0.2f;
	game_object.game.pal-=3;
	if (game_object.game.pal <= 0)
	{
		game_object.game.dis = false;
	}

	/*if (game_object.game.allVec.vec.x > 0)
	{
		game_object.game.allVec.vec.x -= 0.1f;
	}
	else if (game_object.game.allVec.vec.x < 0)
	{
		game_object.game.allVec.vec.x += 0.1f;
	}*/

	game_object.game.allVec.AddPos();
}

void RockEffect::Draw(const Vector2& sc, const Vector2& shake, const int* tex)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
	DrawRotaTex(game_object, tex[texNum], true, shake, sc);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
