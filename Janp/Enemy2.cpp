#include "Enemy2.h"

Enemy2::Enemy2()
{
	game_object = GameObject("Enemy2", false, Vector2(128, 128));
	game_object.color = COLOR(255, 0, 100);
	spawn = false;
	die = false;
	move = false;
}

Enemy2::~Enemy2()
{
}

void Enemy2::Init(std::vector<std::vector<int>>& collMap)
{
	spawn = die;
	if (!spawn)
	{
		for (int y = 0; y < (int)collMap.size(); ++y)
		{
			for (int x = 0; x < (int)collMap[y].size(); ++x)
			{
				if (collMap[y][x] == 71)
				{
					hp = 20;
					spawn = true;
					game_object.game.allVec.pos = Vector2(SIZE * x, SIZE * y);
					game_object.game.dis = true;
					break;
				}
			}
		}
	}
}

void Enemy2::Loading(Load* load)
{

}

void Enemy2::Update(const Vector2& pos, Collision* coll)
{
	if (game_object.game.dis)
	{
		if (game_object.game.dis)
		{
			AllUpdate(0.2f,2.5f);
			PlayerCahck(pos, coll);
		}
	}
}

void Enemy2::PlayerCahck(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.game.allVec.pos;
	const int LAYERSIZE = 128 * 4;
	//‰E


	if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
	{
		game_object.game.allVec.vec.x += 0.6f;
		game_object.game.lr = false;
	}


	//¶

	layer.x -= LAYERSIZE;
	if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
	{
		game_object.game.allVec.vec.x -= 0.6f;
		game_object.game.lr = true;
	}

}

void Enemy2::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}



void Enemy2::Coll(std::vector<Explosion>& ex)
{
	const float BLOWX = 5.5f;
	const float BLOWY = 13.0f;
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;

		if (nameTag == "ex")
		{
			if (!exInvincible.flg)
			{
				exInvincible.flg = true;
				//‰E
				//if (!game_object.game.lr)
				//{
				//	fVec += Vector2(-BLOWX, -BLOWY);
				//}
				////¶
				//else
				//{
				//	fVec += Vector2(BLOWX, -BLOWY);
				//}
				Damage(ex[game_object.coll_Obj_List[i]->num].damage);
				if (DieChack())
				{
					game_object.game.dis = false;
				}
			}
		}
	}
}

void Enemy2::Draw(const Vector2& sc, const Vector2& shake)
{
	Box(game_object, true, shake, sc);
}