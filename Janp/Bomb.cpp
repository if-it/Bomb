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
	exFlg = false;
}

void Bomb::Update(bool& shakeflg, Controller* con, const int& exSound, std::vector<Explosion>& ex)
{
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
			exSpawn(exSound,ex);
			con->Shake(1000, 200);
		}
	}
}

void Bomb::Map_Coll_Update(int(*collMap)[MAPX])
{
	Map_Coll(collMap);
}


void Bomb::Coll(Collision* coll, ALLVECTOR all, Vector2 size, bool& shakeflg, Controller* con, const int& exSound, std::vector<Explosion>& ex)
{
	if (game_object.dis)
	{
		if (coll->Collsion(game_object.allVec.pos, game_object.size.x, game_object.size.y, all.pos, size.x, size.y))
		{
			exSpawn(exSound,ex);
			if (all.vec.y > 0) { all.vec.y = 0; }
			all.vec.y -= EXJUMP;
			con->Shake(1000, 300);
		}
	}


}

void Bomb::Map_Coll(int(*collMap)[MAPX])
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

void Bomb::MapJub(const int& mapPoint, const int& pointNum)
{
	if (pointNum == 0) //Y軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.y -= game_object.allVec.vec.y;
			game_object.allVec.vec.y = 0;
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.y -= game_object.allVec.vec.y;
			game_object.allVec.vec.y = 0;
		}
	}

	else if (pointNum == 2)//X軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.x -= game_object.allVec.vec.x;
			game_object.allVec.vec.x = 0;
		}
	}

	else if (pointNum == 3)//X軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			game_object.allVec.vec.x -= game_object.allVec.vec.x;
			game_object.allVec.vec.x = 0;
		}
	}
}

void Bomb::exSpawn(const int& exSound, std::vector<Explosion>& ex)
{
	game_object.dis = false;

	static Explosion InitEx;
	InitEx.Init();
	InitEx.game_object.dis = true;
	InitEx.game_object.allVec = game_object.allVec;
	ex.push_back(InitEx);
}

void Bomb::Draw(const Vector2& sc, const Vector2& shake, const int* bombTex)
{

	DrawRotaTex(game_object, bombTex[bombAni.num], true, shake, sc);

}


