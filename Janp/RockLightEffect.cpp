#include "RockLightEffect.h"

RockLightEffect::RockLightEffect()
{
}

RockLightEffect::~RockLightEffect()
{
}

void RockLightEffect::Init(const Vector2& pos)
{
	game_object = GameObject();
	game_object.SetPos(pos);
	game_object.game.size = Vector2(0, SIZE * 26);
	size_Vec = 0;
	game_object.game.dis = false;
}

void RockLightEffect::Update()
{
	if (game_object.game.dis)
	{
		game_object.game.pal -= 4;
		if (game_object.game.pal <= 0)
		{
			game_object = GameObject();
			game_object.game.dis = false;
		}
		size_Vec += 0.5f;
		game_object.game.size.x += size_Vec;
		game_object.game.allVec.pos.x -= size_Vec / 2;
	}
}

void RockLightEffect::Draw(const Vector2& sc, const Vector2& shake)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
	Box(game_object, true, shake, sc);
}
