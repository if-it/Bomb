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
	invincible = Count();
	hp = 20;
	fVec = Vector2();
}

void Enemy4::Update()
{
	if (game_object.game.dis)
	{
		EnemyAllUpdate(0.2f, 5.0f);
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
			if (!exInvincible.flg)
			{
				exInvincible.flg = true;
				Damage(ex[game_object.coll_Obj_List[i]->num].damage);

			}
		}
		if (nameTag == "RSideEx" || nameTag == "LSideEx")
		{
			if (!exInvincible.flg)
			{
				exInvincible.flg = true;
				Damage(SIDE_EX_DAMAGE);
			}
		}
	}
}

void Enemy4::MoveChack(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.game.allVec.pos;
	const int LAYERSIZE = SIZE * 10;
	//‰E


	if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
	{
		game_object.game.lr = false;
		game_object.game.allVec.vec.x += 0.8f;
		game_object.game.rota += 10.0f;
	}


	//¶

	layer.x -= LAYERSIZE;
	if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
	{
		game_object.game.lr = true;
		game_object.game.allVec.vec.x -= 0.8f;
		game_object.game.rota -= 10.0f;
	}
}

void Enemy4::Draw(const Vector2& sc, const Vector2& shake, const int& enemy4Tex)
{
	DrawRotaTex(game_object, enemy4Tex, true, shake, sc);
}
