#include "BlockParticle.h"

BlockParticle::BlockParticle()
{
}

BlockParticle::~BlockParticle()
{
}



void BlockParticle::Update()
{
	if (game_object.game.dis)
	{
		game_object.game.allVec.vec.y += 0.1f;

		if (game_object.game.allVec.vec.x > 0)
		{
			game_object.game.allVec.vec.x -= 0.1f;
		}
		else if (game_object.game.allVec.vec.x < 0)
		{
			game_object.game.allVec.vec.x += 0.1f;
		}
		if ((game_object.game.allVec.vec.x < 0 && game_object.game.allVec.vec.x>-0.1f) ||
			(game_object.game.allVec.vec.x > 0 && game_object.game.allVec.vec.x < 0.1f))
		{
			game_object.game.allVec.vec.x = 0;
		}
		game_object.game.pal -= 3;
		game_object.game.allVec.AddPos();
		if (game_object.game.pal <= 0)
		{
			game_object.game.dis = false;
		}
	}
}

void BlockParticle::Draw(const Vector2& sc, const Vector2& shake)
{
	if (game_object.game.dis)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
		Box(game_object, true, shake, sc);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
