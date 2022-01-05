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
	ex_Invincible = Count();
	hp = 8;
	fVec = Vector2();
	move = Count();
	move_End = Count();
	move_lr = 0;
}

void Enemy1::Update()
{
	EnemyAllUpdate(0.2f, 4.0f);

	if (move.Counter(40))
	{
		game_object.game.rota = 0;
		if (move_lr == 1)
		{
			move_lr = 3;
		}
		else if (move_lr == 2)
		{
			move_lr = 4;
		}
	}
	if (move_lr == 3)
	{
		game_object.game.allVec.vec.x += 0.6f;

		move_End.flg = true;
	}
	else if (move_lr == 4)
	{
		game_object.game.allVec.vec.x -= 0.6f;

		move_End.flg = true;
	}
	if (move_End.Counter(120))
	{
		move = Count();
		move_End = Count();
		move_lr = 0;
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
		if (nameTag == "ex" || nameTag == "ex_player")
		{
			if (!ex_Invincible.flg)
			{
				ex_Invincible.flg = true;
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

			}
		}
		if (nameTag == "RSideEx" || nameTag == "LSideEx")
		{
			if (!ex_Invincible.flg)
			{
				ex_Invincible.flg = true;
				Damage(SIDE_EX_DAMAGE);
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
		if (move_lr == 0)
		{
			game_object.game.rota = 315;
			game_object.game.lr = false;
			move.flg = true;
			move_lr = 1;
		}
	}


	//¶

	layer.x -= LAYERSIZE;
	if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
	{
		if (move_lr == 0)
		{
			game_object.game.rota = 45;
			move.flg = true;
			game_object.game.lr = true;
			move_lr = 2;
		}

	}


}

void Enemy1::Draw(const Vector2& sc, const Vector2& shake, const int& tex)
{
	if (blinking)SetDrawBright(128, 128, 128);
	DrawRotaTex(game_object, tex, true, shake, sc);
	SetDrawBright(255, 255, 255);
}

