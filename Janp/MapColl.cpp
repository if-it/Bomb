#include "MapColl.h"



MapColl::MapColl()
{
}


MapColl::~MapColl()
{
}

int MapColl::MapPointer(ALLVECTOR allvec, int x, int y, bool flg, std::vector<std::vector<int>>& collMap)
{
	if (flg)return collMap[(int)((allvec.pos.y + allvec.vec.y + y) / SIZE)][(int)((allvec.pos.x + x) / SIZE)];
	else
	{
		return collMap[(int)((allvec.pos.y + y) / SIZE)][(int)((allvec.pos.x + allvec.vec.x + x) / SIZE)];
	}
}

int MapColl::MapPointer(ALLVECTOR allvec, int x, int y, bool flg, std::vector<std::vector<int>>& collMap, int& xNum, int& yNum)
{
	if (flg)
	{
		xNum = (int)((allvec.pos.x + x) / SIZE);
		yNum = (int)((allvec.pos.y + allvec.vec.y + y) / SIZE);
		return collMap[yNum][xNum];
	}
	else
	{
		xNum = (int)((allvec.pos.x + allvec.vec.x + x) / SIZE);
		yNum = (int)((allvec.pos.y + y) / SIZE);
		return collMap[yNum][xNum];
	}
}

int MapColl::MapPointerX(int x, int y, std::vector<std::vector<int>>& collMap)
{
	return collMap[(int)((game_object.game.allVec.pos.y + y) / SIZE)][(int)((game_object.game.allVec.pos.x + game_object.game.allVec.vec.x + x) / SIZE)];
}

int MapColl::MapPointerX(int x, int y, std::vector<std::vector<int>>& collMap, int& xNum, int& yNum)
{
	xNum = (int)((game_object.game.allVec.pos.x + game_object.game.allVec.vec.x + x) / SIZE);
	yNum = (int)((game_object.game.allVec.pos.y + y) / SIZE);
	return collMap[yNum][xNum];
}

int MapColl::MapPointerY(int x, int y, std::vector<std::vector<int>>& collMap)
{
	return collMap[(int)((game_object.game.allVec.pos.y + game_object.game.allVec.vec.y + y) / SIZE)][(int)((game_object.game.allVec.pos.x + x) / SIZE)];
}

int MapColl::MapPointerY(int x, int y, std::vector<std::vector<int>>& collMap, int& xNum, int& yNum)
{
	xNum = (int)((game_object.game.allVec.pos.x + x) / SIZE);
	yNum = (int)((game_object.game.allVec.pos.y + game_object.game.allVec.vec.y + y) / SIZE);
	return collMap[yNum][xNum];
}

int MapColl::MapPointer(int x, int y, std::vector<std::vector<int>>& collMap, int& xNum, int& yNum)
{
	xNum = (int)((game_object.game.allVec.pos.x + x) / SIZE);
	yNum = (int)((game_object.game.allVec.pos.y + y) / SIZE);
	return collMap[yNum][xNum];
}

int MapColl::MapPointer(Vector2 poss, int x, int y, std::vector<std::vector<int>>& collMap)
{
	return collMap[(int)((poss.y + y) / SIZE)][(int)((poss.x + x) / SIZE)];
}

void MapColl::Map_Coll(std::vector<std::vector<int>>& collMap)
{
	//上左
	MapJub(MapPointerY(1, 1, collMap), 0);
	//上右
	MapJub(MapPointerY(game_object.game.size.x - 1, 1, collMap), 0);

	//下左
	MapJub(MapPointerY(1, game_object.game.size.y - 1, collMap), 1);
	//下右
	MapJub(MapPointerY(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 1);

	game_object.game.allVec.AddPosY();

	//右上
	MapJub(MapPointerX(game_object.game.size.x - 1, 1, collMap), 2);
	//右下
	MapJub(MapPointerX(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 2);

	//左上
	MapJub(MapPointerX(1, 1, collMap), 3);
	//左下
	MapJub(MapPointerX(1, game_object.game.size.y - 1, collMap), 3);

	game_object.game.allVec.AddPosX();
}

void MapColl::MapJub(const int& mapPoint, const int& pointNum)
{
	if (pointNum == 0) //Y軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}

	else if (pointNum == 2)//X軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.x -= game_object.game.allVec.vec.x;
			game_object.game.allVec.vec.x = 0;
		}
	}

	else if (pointNum == 3)//X軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.x -= game_object.game.allVec.vec.x;
			game_object.game.allVec.vec.x = 0;
		}
	}
}