#include "Enemy4.h"

Enemy4::Enemy4()
{
}

Enemy4::~Enemy4()
{
}

void Enemy4::Init(Vector2 pos)
{
	game_object = GameObject("Enemy4", true, Vector2(64.0f, 64.0f));
	game_object.SetPos(pos);
	hp = 35;
	fVec = Vector2();
	move = Count();
	move_End = Count();
	move_lr = 0;
}

void Enemy4::Update()
{
	const float ROTA_SPEED =  20.0f;
	if (game_object.game.dis)
	{
		if (move_lr == 1)
		{
			game_object.game.rota += ROTA_SPEED;

		}
		else if (move_lr == 2)
		{
			game_object.game.rota -= ROTA_SPEED;
		}
		if (move.Conuter(40))
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
			game_object.game.allVec.vec.x += 0.8f;
			game_object.game.rota += ROTA_SPEED;
			move_End.flg = true;
		}
		else if (move_lr == 4)
		{
			game_object.game.allVec.vec.x -= 0.8f;
			game_object.game.rota -= ROTA_SPEED;
			move_End.flg = true;
		}
		if (move_End.Conuter(120))
		{
			move = Count();
			move_End = Count();
			move_lr = 0;
		}
		EnemyAllUpdate(0.2f, 8.0f);
	}
}

void Enemy4::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}

void Enemy4::Coll(std::vector<Explosion>& ex)
{
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "ex")
		{
			if (!ex_Invincible.flg)
			{
				ex_Invincible.flg = true;
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

void Enemy4::MoveChack(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.game.allVec.pos;
	const int LAYERSIZE = SIZE * 20;
	//‰E


	if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
	{
		if (move_lr == 0)
		{
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
			move.flg = true;
			game_object.game.lr = true;
			move_lr = 2;
		}

	}
}

void Enemy4::Draw(const Vector2& sc, const Vector2& shake, const int& enemy4Tex)
{
	if(blinking)SetDrawBright(128,128,128);
	DrawRotaTex(game_object, enemy4Tex, true, shake, sc);
	SetDrawBright(255,255,255);
}
