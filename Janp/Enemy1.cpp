#include "Enemy1.h"

Enemy1::Enemy1()
{
	game_object = GameObject("Enemy1");
}

Enemy1::~Enemy1()
{
}

void Enemy1::Init(Vector2 pos)
{
	game_object.color = COLOR(255, 0, 0);
	game_object.game.allVec.pos = pos;
	invincible = Count();
	exInvincible = Count();
	hp = 4;
	fVec = Vector2();
}

void Enemy1::Update()
{
	if (game_object.game.dis)
	{
		EnemyAllUpdate(0.2f,2.0f);
	}
}

void Enemy1::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}



void Enemy1::Coll(std::vector<Explosion>& ex)
{
	const float BLOWX = 5.5f;
	const float BLOWY = 13.0f;
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "Player")
		{
			if (!invincible.flg)
			{
				invincible.flg = true;
				//‰E
				if (!game_object.game.lr)
				{
					fVec += Vector2(-BLOWX, -BLOWY);
				}
				//¶
				else
				{
					fVec += Vector2(BLOWX,-BLOWY);
				}
			}
		}
		if (nameTag == "ex")
		{
			if (!exInvincible.flg)
			{
				exInvincible.flg = true;
				//‰E
				if (!game_object.game.lr)
				{
					fVec += Vector2(-BLOWX, -BLOWY);
				}
				//¶
				else
				{
					fVec += Vector2(BLOWX, -BLOWY);
				}
				Damage(ex[game_object.coll_Obj_List[i]->num].damage);
				if (DieChack())
				{
					game_object.game.dis = false;
				}
			}
		}
	}
}

void Enemy1::MoveChack(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.game.allVec.pos;
	const int LAYERSIZE = SIZE * 10;
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

void Enemy1::Draw(const Vector2& sc, const Vector2& shake)
{
	Box(game_object, true, shake, sc);;
}

