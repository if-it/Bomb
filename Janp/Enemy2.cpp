#include "Enemy2.h"

Enemy2::Enemy2()
{
	game_object = GameObject("Enemy2Tex", false, Vector2(128, 128));
	game_object.color = COLOR(255, 0, 100);
	spawn = false;
	die = false;
	move = false;
	attack = Count();

	arm = GameObject("Enemy2", false, Vector2(128, 64));
	arm.color = COLOR(255, 0, 0);

	body = GameObject("Enemy2", false, Vector2(80, 128));
	body.color = COLOR(255, 150, 50);

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
					attack = Count();

					arm.game.dis = true;
					arm.SetPos(Vector2(game_object.GetPos().x - 64, game_object.GetPos().y + 32));

					body.game.dis = true;
					body.SetPos(Vector2(game_object.GetPos().x + 32, game_object.GetPos().y));
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
		if (!die)
		{
			bool lr = game_object.game.lr;
			AllUpdate(0.2f, 2.5f);
			PlayerCahck(pos, coll);
			body.game.lr = lr;
			arm.game.lr = lr;

			if (lr)body.SetPos(Vector2(game_object.GetPos().x + 32, game_object.GetPos().y));

			else body.SetPos(Vector2(game_object.GetPos().x + 16, game_object.GetPos().y));

			if (attack.Conuter(10))
			{
				if (lr)
				{
					arm.game.allVec.vec.x -= 10.0f;
				}
				else
				{
					arm.game.allVec.vec.x += 10.0f;
				}

				arm.game.allVec.AddPos();
			}
			else
			{
				if (lr)arm.SetPos(Vector2(game_object.GetPos().x - 64, game_object.GetPos().y + 32));
				else arm.SetPos(Vector2(game_object.GetPos().x + 64, game_object.GetPos().y + 32));
			}
		}
	}
}

void Enemy2::PlayerCahck(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.GetPos();
	const int LAYERSIZE = 128 * 4;
	float distanceL = Vector2::Distance(Vector2(pos.x + SIZE * 2, pos.y), game_object.GetPos());
	float distanceR = Vector2::Distance(pos, Vector2(game_object.GetPos().x + game_object.game.size.x, game_object.GetPos().y));

	if (distanceL <= 120 )
	{
		attack.flg = true;
		game_object.game.lr = true;
	}
	else if (distanceR <= 120)
	{
		attack.flg = true;
		game_object.game.lr = false;
	}
	else
	{
		attack = Count();
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
	Box(arm, false, shake, sc);
	Box(body, false, shake, sc);

}