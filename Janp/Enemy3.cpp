#include "Enemy3.h"

Enemy3::Enemy3()
{
}

Enemy3::~Enemy3()
{
}

void Enemy3::Init(Vector2 pos)
{
	game_object.color = COLOR(255, 0, 0);
	game_object.game.allVec.pos = pos;
	invincible = Count();
	exInvincible = Count();
	hp = 4;
	fVec = Vector2();
}

void Enemy3::Update()
{
	if (game_object.game.dis)
	{
		EnemyAllUpdate(0.2f, 2.0f);
	}
}

void Enemy3::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
}

void Enemy3::Coll(std::vector<Explosion>& ex)
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

void Enemy3::MoveChack(const Vector2& pos, Collision* coll)
{
}

void Enemy3::Draw(const Vector2& sc, const Vector2& shake)
{
}
