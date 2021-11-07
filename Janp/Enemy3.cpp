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
	game_object.SetPos(pos);
	ex_Invincible = Count();
	hp = 5;
	fVec = Vector2();
}

void Enemy3::Update()
{

	if (game_object.game.lr)
	{
		//��
		game_object.game.allVec.vec.x -= 0.4f;
	}
	else
	{
		//�E
		game_object.game.allVec.vec.x += 0.4f;
	}
	EnemyAllUpdate(0.2f, 1.5f);

}

void Enemy3::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{

	//�㍶
	Map_Jub(MapPointerY(1, 1, collMap), 0);
	//��E
	Map_Jub(MapPointerY(game_object.game.size.x - 1, 1, collMap), 0);

	//����
	Map_Jub(MapPointerY(1, game_object.game.size.y - 1, collMap), 1);
	//���E
	Map_Jub(MapPointerY(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 1);

	game_object.game.allVec.AddPosY();

	//�E��
	Map_Jub(MapPointerX(game_object.game.size.x - 1, 1, collMap), 2);
	//�E��
	Map_Jub(MapPointerX(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 2);

	//����
	Map_Jub(MapPointerX(1, 1, collMap), 3);
	//����
	Map_Jub(MapPointerX(1, game_object.game.size.y - 1, collMap), 3);

	game_object.game.allVec.AddPosX();
}

void Enemy3::Map_Jub(const int& mapPoint, const int& pointNum)
{
	if (pointNum == 0) //Y��
	{
		if (WALL)
		{
			//game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}
	else if (pointNum == 1) //Y��
	{
		if (WALL)
		{
			//game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}

	else if (pointNum == 2)//X��
	{
		if (WALL)
		{
			//game_object.game.allVec.vec.x -= game_object.game.allVec.vec.x;
			game_object.game.allVec.vec.x = 0;
			game_object.game.lr = true;
		}
	}

	else if (pointNum == 3)//X��
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
			if (!ex_Invincible.flg)
			{
				ex_Invincible.flg = true;
				//�E
				if (!game_object.game.lr)
				{
					fVec += Vector2(-BLOWX, -BLOWY);
				}
				//��
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


void Enemy3::Draw(const Vector2& sc, const Vector2& shake, const int& tex)
{
	if (blinking)SetDrawBright(128, 128, 128);
	DrawRotaTex(game_object, tex, true, shake, sc);
	SetDrawBright(255, 255, 255);
}
