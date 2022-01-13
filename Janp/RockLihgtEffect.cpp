#include "RockLihgtEffect.h"

RockLihgtEffect::RockLihgtEffect()
{
}

RockLihgtEffect::~RockLihgtEffect()
{
}

void RockLihgtEffect::Init(const Vector2& pos)
{
	game_object = GameObject();
	game_object.SetPos(pos);
	game_object.game.size = Vector2(8, HEIGHT);
	size_Vec = 0;
}

void RockLihgtEffect::Update()
{
	--game_object.game.pal;
	if (game_object.game.pal <= 0)
	{
		game_object = GameObject();
		game_object.game.dis = false;
	}
	size_Vec += 0.5f;
	game_object.game.size.x += size_Vec;
}

void RockLihgtEffect::Draw(const Vector2& sc, const Vector2& shake)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
	Box(game_object, true, shake, sc);
}
