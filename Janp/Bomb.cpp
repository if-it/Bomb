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
	ex = GameObject(false);
	bombAni = ANIMATION();
	exAni = ANIMATION();
	time = 0;
	exFlg = false;
}

void Bomb::Update(bool& shakeflg, Controller* con)
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
			//exSpawn(shakeflg);
			con->Shake(1000, 200);
		}
	}
	if (ex.dis)
	{
		if (exAni.OneAnimation(10, 4))
		{
			ex = GameObject(false);
		}
	}
}

void Bomb::Map_Coll_Update(int(*collMap)[MAPX])
{
	Map_Coll(collMap);
}


void Bomb::Coll(Collision* coll, ALLVECTOR all, Vector2 size, bool& shakeflg, Controller* con, const int& exSound)
{

	if (ex.dis)
	{
		if (!exFlg && coll->Collsion(ex.allVec.pos, SIZE, SIZE, all.pos, size.x, size.y))
		{
			exFlg = true;
		}
	}
	if (game_object.dis)
	{
		if (coll->Collsion(game_object.allVec.pos, game_object.size.x, game_object.size.y, all.pos, size.x, size.y))
		{
			//exSpawn(shakeflg,exSound);
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

void Bomb::exSpawn(bool& shakeflg, const int& exSound)
{
	ex.allVec.pos = game_object.allVec.pos;
	game_object.dis = false;
	ex.dis = true;
	exAni = ANIMATION();
	ex.allVec = game_object.allVec;
	shakeflg = true;
	PlaySoundMem(exSound, DX_PLAYTYPE_BACK, true);
}

void Bomb::Draw(const Vector2& sc, const Vector2& shake, const int* bombTex)
{

	DrawRotaTex(game_object, bombTex[bombAni.num], true, shake, sc);
	//DrawRotaTex(ex, exTex[exAni.num], true, shake, sc);

}


