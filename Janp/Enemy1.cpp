#include "Enemy1.h"

Enemy1::Enemy1()
{

}

Enemy1::~Enemy1()
{
}

void Enemy1::Init(Vector2 pos)
{
	game_object = GameObject();
	game_object.color = COLOR(255, 0, 0);
	game_object.allVec.pos = pos;
	invincible = Count();
}

void Enemy1::Update()
{
	const float ENEMY1_SPEED = 0.3f; //エネミーの速さ
	const float ENEMY1_MAX_SPEED = 5.0f; //最大の速さ
	if (game_object.dis)
	{
		game_object.allVec.vec.y += 0.2f;
		if (game_object.allVec.vec.x > 0)
		{
			game_object.allVec.vec.x -= ENEMY1_SPEED;
		}
		else if (game_object.allVec.vec.x < 0)
		{
			game_object.allVec.vec.x += ENEMY1_SPEED;
		}
		if ((game_object.allVec.vec.x < 0 && game_object.allVec.vec.x>-ENEMY1_SPEED) || (game_object.allVec.vec.x > 0 && game_object.allVec.vec.x < ENEMY1_SPEED))
		{
			game_object.allVec.vec.x = 0;
		}

		if (game_object.allVec.vec.x > ENEMY1_MAX_SPEED)
		{
			game_object.allVec.vec.x = ENEMY1_MAX_SPEED;
		}
		if (game_object.allVec.vec.x < -ENEMY1_MAX_SPEED)
		{
			game_object.allVec.vec.x = -ENEMY1_MAX_SPEED;
		}

		invincible.Conuter(60);
	}
}

void Enemy1::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}

void Enemy1::Map_Coll(std::vector<std::vector<int>>& collMap)
{
	//上左
	MapJub(MapPointerY(1, 1, collMap), 0);
	//上右
	MapJub(MapPointerY(game_object.size.x - 1, 1, collMap), 0);

	//下左
	MapJub(MapPointerY(1, game_object.size.y - 1, collMap), 1);
	//下右
	MapJub(MapPointerY(game_object.size.x - 1, game_object.size.y - 1, collMap), 1);

	game_object.allVec.AddPosY();

	//右上
	MapJub(MapPointerX(game_object.size.x - 1, 1, collMap), 2);
	//右下
	MapJub(MapPointerX(game_object.size.x - 1, game_object.size.y - 1, collMap), 2);

	//左上
	MapJub(MapPointerX(1, 1, collMap), 3);
	//左下
	MapJub(MapPointerX(1, game_object.size.y - 1, collMap), 3);

	game_object.allVec.AddPosX();
}

void Enemy1::MapJub(const int& mapPoint, const int& pointNum)
{
	if (pointNum == 0) //Y軸
	{
		if (WALL)
		{
			game_object.allVec.vec.y -= game_object.allVec.vec.y;
			game_object.allVec.vec.y = 0;
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (WALL)
		{
			game_object.allVec.vec.y -= game_object.allVec.vec.y;
			game_object.allVec.vec.y = 0;
		}
	}

	else if (pointNum == 2)//X軸
	{
		if (WALL)
		{
			game_object.allVec.vec.x -= game_object.allVec.vec.x;
			game_object.allVec.vec.x = 0;
		}
	}

	else if (pointNum == 3)//X軸
	{
		if (WALL)
		{
			game_object.allVec.vec.x -= game_object.allVec.vec.x;
			game_object.allVec.vec.x = 0;
		}
	}
}

void Enemy1::PlayerColl()
{
	if (!invincible.flg)
	{
		invincible.flg = true;
		//右
		if (!game_object.lr)
		{
			game_object.allVec.vec += Vector2(-10, -3);
		}
		//左
		else
		{
			game_object.allVec.vec += Vector2(10, -3);
		}
	}
}

void Enemy1::MoveChack(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.allVec.pos;
	const int LAYERSIZE = SIZE*5;
	//右


	if (coll->Collsion(layer, LAYERSIZE, game_object.size.y, pos, SIZE * 2, SIZE * 2))
	{
		game_object.allVec.vec.x += 1.5f;
		game_object.lr = false;
	}


	//左

	layer.x -= LAYERSIZE;
	if (coll->Collsion(layer, LAYERSIZE, game_object.size.y, pos, SIZE * 2, SIZE * 2))
	{
		game_object.allVec.vec.x -= 1.5f;
		game_object.lr = true;
	}


}

void Enemy1::Draw(const Vector2& sc, const Vector2& shake)
{
	Box(game_object, true, shake, sc);;
}

