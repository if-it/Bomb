#include "Bomb.h"



Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

void Bomb::Init()
{
	game_object = GameObject(false);
	bombAni = ANIMATION();
	time = 0;
	playerOneColl = false;
	playerSpawn = false;
}

void Bomb::Update(bool& shakeflg, Controller* con, ExplosionMana* ex)
{
	time++;
	if (game_object.dis)
	{
		game_object.allVec.vec.y += 0.1f;

		if (game_object.allVec.vec.x > 0)
		{
			game_object.allVec.vec.x -= 0.1f;
		}
		else if (game_object.allVec.vec.x < 0)
		{
			game_object.allVec.vec.x += 0.1f;
		}
		if ((game_object.allVec.vec.x < 0 && game_object.allVec.vec.x>-0.1f) ||
			(game_object.allVec.vec.x > 0 && game_object.allVec.vec.x < 0.1f))
		{
			game_object.allVec.vec.x = 0;
		}

		if (bombAni.OneAnimation(30, 8))
		{
			game_object.dis = false;
			ex->ExSpawn(game_object);
			con->Shake(1000, 200);
		}
		if (time == 60)
		{
			playerOneColl = false;
		}
	}
}

void Bomb::Map_Coll_Update(std::vector<std::vector<int>>& collMap)
{
	if(game_object.dis)Map_Coll(collMap);
}


void Bomb::Coll(Collision* coll, ALLVECTOR& all, Vector2 size, bool& shakeflg, Controller* con, ExplosionMana* ex)
{
	if (game_object.dis)
	{
		//player
		bool playerColl = coll->Collsion(game_object.allVec.pos, game_object.size.x, game_object.size.y, all.pos, size.x, size.y);

		if (playerOneColl && !playerColl)playerOneColl = false;

		if (!playerOneColl && playerColl)
		{
			game_object.dis = false;
			ex->ExSpawn(game_object);
			all.vec.y = 0;
			all.vec.y -= EXJUMP;
			con->Shake(1000, 300);
		}
	}
}

void Bomb::Map_Coll(std::vector<std::vector<int>>& collMap)
{
	//�㍶
	MapJub(MapPointerY(1, 1, collMap), 0);
	//��E
	MapJub(MapPointerY(game_object.size.x - 1, 1, collMap), 0);

	//����
	MapJub(MapPointerY(1, game_object.size.y - 1, collMap), 1);
	//���E
	MapJub(MapPointerY(game_object.size.x - 1, game_object.size.y - 1, collMap), 1);

	game_object.allVec.AddPosY();

	//�E��
	MapJub(MapPointerX(game_object.size.x - 1, 1, collMap), 2);
	//�E��
	MapJub(MapPointerX(game_object.size.x - 1, game_object.size.y - 1, collMap), 2);

	//����
	MapJub(MapPointerX(1, 1, collMap), 3);
	//����
	MapJub(MapPointerX(1, game_object.size.y - 1, collMap), 3);

	game_object.allVec.AddPosX();
}

void Bomb::MapJub(const int& mapPoint, const int& pointNum)
{
	if (pointNum == 0) //Y��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.y -= game_object.allVec.vec.y;
			game_object.allVec.vec.y = 0;
		}
	}
	else if (pointNum == 1) //Y��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.y -= game_object.allVec.vec.y;
			game_object.allVec.vec.y = 0;
		}
	}

	else if (pointNum == 2)//X��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.x -= game_object.allVec.vec.x;
			game_object.allVec.vec.x = 0;
		}
	}

	else if (pointNum == 3)//X��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.x -= game_object.allVec.vec.x;
			game_object.allVec.vec.x = 0;
		}
	}
}

//void Bomb::exSpawn(const int& exSound, std::vector<Explosion>& ex)
//{
//	game_object.dis = false;
//
//	static Explosion InitEx;
//	InitEx.Init();
//	InitEx.game_object.dis = true;
//	InitEx.game_object.allVec = game_object.allVec;
//	InitEx.game_object.allVec.pos -= SIZE/2;
//	ex.push_back(InitEx);
//}

void Bomb::Draw(const Vector2& sc, const Vector2& shake, const int* bombTex)
{

	DrawRotaTex(game_object, bombTex[bombAni.num], true, shake, sc);

}


