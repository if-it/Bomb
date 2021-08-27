#include "Enemy3.h"

Enemy3::Enemy3()
{
}

Enemy3::~Enemy3()
{
}

void Enemy3::Init(Vector2 pos)
{
	game_object = GameObject("Enemy3");
	game_object.color = COLOR(255, 0, 0);
	game_object.game.allVec.pos = pos;
	invincible = Count();
	exInvincible = Count();
	hp = 3;
	fVec = Vector2();
}

void Enemy3::Update()
{
	if (game_object.game.dis)
	{
		if (game_object.game.lr)
		{
			//左
			game_object.game.allVec.vec.x -= 0.4f;
		}
		else
		{
			//右
			game_object.game.allVec.vec.x += 0.4f;
		}
		EnemyAllUpdate(0.2f, 1.5f);
	}
}

void Enemy3::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{

	//上左
	Map_Jub(MapPointerY(1, 1, collMap), 0);
	//上右
	Map_Jub(MapPointerY(game_object.game.size.x - 1, 1, collMap), 0);

	//下左
	Map_Jub(MapPointerY(1, game_object.game.size.y - 1, collMap), 1);
	//下右
	Map_Jub(MapPointerY(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 1);

	game_object.game.allVec.AddPosY();

	//右上
	Map_Jub(MapPointerX(game_object.game.size.x - 1, 1, collMap), 2);
	//右下
	Map_Jub(MapPointerX(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 2);

	//左上
	Map_Jub(MapPointerX(1, 1, collMap), 3);
	//左下
	Map_Jub(MapPointerX(1, game_object.game.size.y - 1, collMap), 3);

	game_object.game.allVec.AddPosX();
}

void Enemy3::Map_Jub(const int& mapPoint, const int& pointNum)
{
	if (pointNum == 0) //Y軸
	{
		if (WALL)
		{
			//game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (WALL)
		{
			//game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}

	else if (pointNum == 2)//X軸
	{
		if (WALL)
		{
			//game_object.game.allVec.vec.x -= game_object.game.allVec.vec.x;
			game_object.game.allVec.vec.x = 0;
 			game_object.game.lr = true;
		}
	}

	else if (pointNum == 3)//X軸
	{
		if (WALL)
		{
			//game_object.game.allVec.vec.x -= game_object.game.allVec.vec.x;
			game_object.game.allVec.vec.x = 0;
			game_object.game.lr = false;
		}
	}
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
				//右
				if (!game_object.game.lr)
				{
					fVec += Vector2(-BLOWX, -BLOWY);
				}
				//左
				else
				{
					fVec += Vector2(BLOWX, -BLOWY);
				}
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


void Enemy3::Draw(const Vector2& sc, const Vector2& shake , const int& tex)
{
	DrawRotaTex(game_object, tex, true, shake, sc);
}
