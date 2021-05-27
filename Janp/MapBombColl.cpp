#include "MapBombColl.h"



MapBombColl::MapBombColl()
{
}


MapBombColl::~MapBombColl()
{
}

void MapBombColl::MapColl(int(*collMap)[MAPX], GameObject & chara, int sizeX, int sizeY, int SizeCut)
{
	//上左
	MapJub(MapPointer(chara.allVec, SizeCut + 1, SizeCut + 1, true, collMap), chara, 0);
	//上右
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, SizeCut + 1, true, collMap), chara, 0);

	//下左
	MapJub(MapPointer(chara.allVec, SizeCut + 1, sizeY - SizeCut - 1, true, collMap), chara, 1);
	//下右
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, sizeY - SizeCut - 1, true, collMap), chara, 1);

	chara.allVec.AddPosY();

	//右上
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, SizeCut + 1, false, collMap), chara, 2);
	//右下
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, sizeY - SizeCut - 1, false, collMap), chara, 2);

	//左上
	MapJub(MapPointer(chara.allVec, SizeCut + 1, SizeCut + 1, false, collMap), chara, 3);
	//左下
	MapJub(MapPointer(chara.allVec, SizeCut + 1, sizeY - SizeCut - 1, false, collMap), chara, 3);

	chara.allVec.AddPosX();
}

void MapBombColl::MapJub(int mapPoint, GameObject & chara, int XY)
{
	if (XY == 0) //Y軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23)||mapPoint==40)
		{
			chara.allVec.vec.y -= chara.allVec.vec.y;
			chara.allVec.vec.y = 0;
		}
	}
	else if (XY == 1) //Y軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			chara.allVec.vec.y -= chara.allVec.vec.y;
			chara.allVec.vec.y = 0;
		}
	}

	else if (XY == 2)//X軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			chara.allVec.vec.x -= chara.allVec.vec.x;
			chara.allVec.vec.x = 0;
		}
	}

	else if (XY == 3)//X軸
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			chara.allVec.vec.x -= chara.allVec.vec.x;
			chara.allVec.vec.x = 0;
		}
	}
}
