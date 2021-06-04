#include "MapColl.h"



MapColl::MapColl()
{
}


MapColl::~MapColl()
{
}

int MapColl::MapPointer(ALLVECTOR allvec, int x, int y, bool flg, int(*collMap)[MAPX])
{
	if (flg)return collMap[(int)((allvec.pos.y + allvec.vec.y + y) / SIZE)][(int)((allvec.pos.x + x) / SIZE)];
	else
	{
		return collMap[(int)((allvec.pos.y + y) / SIZE)][(int)((allvec.pos.x + allvec.vec.x + x) / SIZE)];
	}
}

int MapColl::MapPointer(ALLVECTOR allvec, int x, int y, bool flg, int(*collMap)[MAPX], int & xNum, int & yNum)
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

int MapColl::MapPointerX(int x, int y, int(*collMap)[MAPX], int& xNum, int& yNum)
{
	xNum = (int)((game_object.allVec.pos.x + game_object.allVec.vec.x + x) / SIZE);
	yNum = (int)((game_object.allVec.pos.y + y) / SIZE);
	return collMap[yNum][xNum];
}

int MapColl::MapPointerY(int x, int y, int(*collMap)[MAPX], int& xNum, int& yNum)
{
	xNum = (int)((game_object.allVec.pos.x + x) / SIZE);
	yNum = (int)((game_object.allVec.pos.y + game_object.allVec.vec.y + y) / SIZE);
	return collMap[yNum][xNum];
}

int MapColl::MapPointer(Vector2 poss, int x, int y, int(*collMap)[MAPX])
{
	return collMap[(int)((poss.y + y) / SIZE)][(int)((poss.x + x) / SIZE)];
}
