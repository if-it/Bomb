#include "Enemy2.h"

Enemy2::Enemy2()
{
	game_object = GameObject("Enemy2", false, Vector2(128, 128));
	spawn = false;
	die = false;
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

void Enemy2::Update()
{
	if (game_object.game.dis)
	{
		game_object.game.allVec.vec.y += 0.2f;
		AllUpdate();
	}
}

void Enemy2::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}



void Enemy2::Coll(std::vector<Explosion>& ex)
{
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;

		if (nameTag == "ex")
		{
			if (!exInvincible.flg)
			{
				exInvincible.flg = true;
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
	Box(game_object, true, shake, sc, game_object.game.size.x, game_object.game.size.y);
}