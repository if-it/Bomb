#include "Explosion.h"


Explosion::Explosion()
{
	game_object = GameObject(true, Vector2(64.0f, 64.0f));
}

Explosion::~Explosion()
{
}

void Explosion::Init()
{
	game_object = GameObject(false, Vector2(64.0f, 64.0f));
	exAni = ANIMATION();
}

void Explosion::Update()
{
	if (exAni.OneAnimation(10, 4))
	{
		game_object = GameObject(false);
	}
}

void Explosion::Map_Coll_Update(int(*collMap)[MAPX])
{
}

void Explosion::Coll(Collision* coll, ALLVECTOR all, Vector2 size)
{
}

void Explosion::Draw(const Vector2& sc, const Vector2& shake, const int* exTex)
{
	DrawRotaTex(game_object, exTex[exAni.num], true, shake, sc);
}

void Explosion::Map_Coll(int(*collMap)[MAPX])
{
	static int SizeCut = 0;
	//上左
	MapJub(MapPointer(SizeCut + 1, SizeCut + 1, collMap, xNum[0], yNum[0]), 0, collMap);

	//上真ん中
	MapJub(MapPointer(game_object.size.x / 2, SizeCut + 1, collMap, xNum[1], yNum[1]), 1, collMap);

	//上右
	MapJub(MapPointer(game_object.size.x - SizeCut - 1, SizeCut + 1, collMap, xNum[2], yNum[2]), 2, collMap);

	//右真ん中
	MapJub(MapPointer(game_object.size.x - SizeCut - 1, game_object.size.y / 2, collMap, xNum[3], yNum[3]), 3, collMap);

	//中心
	MapJub(MapPointer((game_object.size.x - SizeCut) / 2, (game_object.size.y - SizeCut) / 2, collMap, xNum[4], yNum[4]), 4, collMap);

	//左真ん中
	MapJub(MapPointer(SizeCut + 1, game_object.size.y / 2, collMap, xNum[5], yNum[5]), 5, collMap);

	//下左
	MapJub(MapPointer(SizeCut + 1, game_object.size.y - SizeCut - 1, collMap, xNum[6], yNum[6]), 6, collMap);

	//下真ん中
	MapJub(MapPointer(game_object.size.x / 2, game_object.size.y - SizeCut - 1, collMap, xNum[7], yNum[7]), 7, collMap);

	//下右
	MapJub(MapPointer(game_object.size.x - SizeCut - 1, game_object.size.y - SizeCut - 1, collMap, xNum[8], yNum[8]), 8, collMap);
}

void Explosion::MapJub(const int& mapPoint, const int& pointNum, int(*collMap)[MAPX])
{
	if (pointNum == 0)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[0]][yNum[0]] = 0;
			break;
		case 40:
			collMap[xNum[0]][yNum[0]] = 41;
			break;
		default:
			break;
		}
	}
	else if (pointNum == 1)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[1]][yNum[1]] = 0;
			break;
		case 40:
			collMap[xNum[1]][yNum[1]] = 41;
			break;
		default:
			break;
		}
	}
	else if (pointNum == 2)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[2]][yNum[2]] = 0;
			break;
		case 40:
			collMap[xNum[2]][yNum[2]] = 41;
			break;
		default:
			break;
		}
	}
	else if (pointNum == 3)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[3]][yNum[3]] = 0;
			break;
		case 40:
			collMap[xNum[3]][yNum[3]] = 41;
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 4))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[4]][yNum[4]] = 0;
			break;
		case 40:
			collMap[xNum[4]][yNum[4]] = 41;
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 5))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[5]][yNum[5]] = 0;
			break;
		case 40:
			collMap[xNum[5]][yNum[5]] = 41;
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 6))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[6]][yNum[6]] = 0;
			break;
		case 40:
			collMap[xNum[6]][yNum[6]] = 41;
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 7))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[xNum[7]][yNum[7]] = 0;
			break;
		case 40:
			collMap[xNum[7]][yNum[7]] = 41;
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 8))
	{
	switch (mapPoint)
	{
	case 3:
		collMap[xNum[8]][yNum[8]] = 0;
		break;
	case 40:
		collMap[xNum[8]][yNum[8]] = 41;
		break;
	default:
		break;
	}
	}
}
