#include "MapBombColl.h"



MapBombColl::MapBombColl()
{
}


MapBombColl::~MapBombColl()
{
}

void MapBombColl::MapColl(int(*collMap)[MAPX], GameObject & chara, int sizeX, int sizeY, int SizeCut)
{
	//�㍶
	MapJub(MapPointer(chara.allVec, SizeCut + 1, SizeCut + 1, true, collMap), chara, 0);
	//��E
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, SizeCut + 1, true, collMap), chara, 0);

	//����
	MapJub(MapPointer(chara.allVec, SizeCut + 1, sizeY - SizeCut - 1, true, collMap), chara, 1);
	//���E
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, sizeY - SizeCut - 1, true, collMap), chara, 1);

	chara.allVec.AddPosY();

	//�E��
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, SizeCut + 1, false, collMap), chara, 2);
	//�E��
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, sizeY - SizeCut - 1, false, collMap), chara, 2);

	//����
	MapJub(MapPointer(chara.allVec, SizeCut + 1, SizeCut + 1, false, collMap), chara, 3);
	//����
	MapJub(MapPointer(chara.allVec, SizeCut + 1, sizeY - SizeCut - 1, false, collMap), chara, 3);

	chara.allVec.AddPosX();
}

void MapBombColl::MapJub(int mapPoint, GameObject & chara, int XY)
{
	if (XY == 0) //Y��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23)||mapPoint==40)
		{
			chara.allVec.vec.y -= chara.allVec.vec.y;
			chara.allVec.vec.y = 0;
		}
	}
	else if (XY == 1) //Y��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			chara.allVec.vec.y -= chara.allVec.vec.y;
			chara.allVec.vec.y = 0;
		}
	}

	else if (XY == 2)//X��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			chara.allVec.vec.x -= chara.allVec.vec.x;
			chara.allVec.vec.x = 0;
		}
	}

	else if (XY == 3)//X��
	{
		if (mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40)
		{
			chara.allVec.vec.x -= chara.allVec.vec.x;
			chara.allVec.vec.x = 0;
		}
	}
}
