#include "RockAttack.h"

RockAttack::RockAttack()
{
}

RockAttack::~RockAttack()
{
}

void RockAttack::Init(const Vector2 pos)
{
	const int RATESPEED = 20;

	game_object = GameObject("RockAttack",true,Vector2(16.0f,16.0f));
	game_object.SetPos(pos);
	rate = GetRand(RATESPEED) - GetRand(RATESPEED);
}

void RockAttack::Update()
{
	if (game_object.game.allVec.pos.y>3000)
	{
		game_object.game.dis = false;
	}
	const float SPEED = 10.0f;
	game_object.game.allVec.vec.y += 0.1f;
	if (game_object.game.allVec.vec.y > SPEED)
	{
		game_object.game.allVec.vec.y = SPEED;
	}
	game_object.game.rota += rate;
	game_object.game.allVec.AddPos();

}

void RockAttack::Coll()
{
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "Player")
		{
			game_object.game.dis = false;
		}
		if (nameTag == "ex")
		{
			game_object.game.dis = false;
		}
	}
}

void RockAttack::Draw(const Vector2& sc, const Vector2& shake, const int& tex)
{
	DrawRotaTex(game_object, tex, true, shake, sc);
}
