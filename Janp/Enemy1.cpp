#include "Enemy1.h"

Enemy1::Enemy1()
{

}

Enemy1::~Enemy1()
{
}

void Enemy1::Init(Vector2 pos)
{
	game_object = GameObject("Enemy1");
	game_object.color = COLOR(255, 0, 0);
	game_object.game.allVec.pos = pos;
	invincible = Count();
	exInvincible = Count();
	hp = 3;
	fVec = Vector2();
}

void Enemy1::Update()
{

	const float ENEMY1_SPEED = 0.6f; //�G�l�~�[�̑���
	const float ENEMY1_MAX_SPEED = 3.0f; //�ő�̑���
	if (game_object.game.dis)
	{
		if (DieChack())
		{
			game_object.game.dis = false;
		}
		game_object.game.allVec.vec.y += 0.2f;
		if (game_object.game.allVec.vec.x > 0)
		{
			game_object.game.allVec.vec.x -= ENEMY1_SPEED;
		}
		else if (game_object.game.allVec.vec.x < 0)
		{
			game_object.game.allVec.vec.x += ENEMY1_SPEED;
		}
		if ((game_object.game.allVec.vec.x < 0 && game_object.game.allVec.vec.x>-ENEMY1_SPEED) ||
			(game_object.game.allVec.vec.x > 0 && game_object.game.allVec.vec.x < ENEMY1_SPEED))
		{
			game_object.game.allVec.vec.x = 0;
		}

		if (game_object.game.allVec.vec.x > ENEMY1_MAX_SPEED)
		{
			game_object.game.allVec.vec.x = ENEMY1_MAX_SPEED;
		}
		if (game_object.game.allVec.vec.x < -ENEMY1_MAX_SPEED)
		{
			game_object.game.allVec.vec.x = -ENEMY1_MAX_SPEED;
		}
		game_object.game.allVec.vec += fVec;
		fVec = Vector2();
		AllUpdate();
	}
}

void Enemy1::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}



void Enemy1::Coll(std::vector<Explosion>& ex)
{
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "Player")
		{
			if (!invincible.flg)
			{
				invincible.flg = true;
				//�E
				if (!game_object.game.lr)
				{
					fVec += Vector2(-10, -3);
				}
				//��
				else
				{
					fVec += Vector2(10, -3);
				}
			}
		}
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

void Enemy1::MoveChack(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.game.allVec.pos;
	const int LAYERSIZE = SIZE * 5;
	//�E


	if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
	{
		game_object.game.allVec.vec.x += 0.6f;
		game_object.game.lr = false;
	}


	//��

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

