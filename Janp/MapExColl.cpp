#include "MapExColl.h"



MapExColl::MapExColl()
{
}


MapExColl::~MapExColl()
{
}

void MapExColl::MapColl(int(*collMap)[MAPX], const Vector2 & pos, int sizeX, int sizeY, int SizeCut, bool flg)
{
	if (flg)
	{
		//上左
		MapJub(MapPointer(pos, SizeCut + 1, SizeCut + 1, collMap), pos, 0, collMap, true);
		//上右
		MapJub(MapPointer(pos, sizeX - SizeCut - 1, SizeCut + 1, collMap), pos, 1, collMap, true);

		//下左
		MapJub(MapPointer(pos, SizeCut + 1, sizeY - SizeCut - 1, collMap), pos, 2, collMap, true);
		//下右
		MapJub(MapPointer(pos, sizeX - SizeCut - 1, sizeY - SizeCut - 1, collMap), pos, 3, collMap, true);
	}
	else
	{

		//上左
		MapJub(MapPointer(Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), SizeCut + 1, SizeCut + 1, collMap),
			Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), 0, collMap, false);
		//上右
		MapJub(MapPointer(Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), sizeX - SizeCut - 1, SizeCut + 1, collMap),
			Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), 1, collMap, false);

		//下左
		MapJub(MapPointer(Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), SizeCut + 1, sizeY - SizeCut - 1, collMap),
			Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), 2, collMap, false);
		//下右
		MapJub(MapPointer(Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), sizeX - SizeCut - 1, sizeY - SizeCut - 1, collMap),
			Vector2(pos.x - SIZE / 2, pos.y - SIZE / 2), 3, collMap, false);

		//真ん中上
		MapJub(MapPointer(Vector2(pos.x + 1, pos.y - SIZE / 2), 0, 0, collMap),
			Vector2(pos.x + 1, pos.y - SIZE / 2), 4, collMap, false);

		//真ん中下
		MapJub(MapPointer(Vector2(pos.x + 1, pos.y + SIZE * 1.5f), 0, 0, collMap),
			Vector2(pos.x + 1, pos.y + SIZE * 1.5f), 4, collMap, false);

		//真ん中左
		MapJub(MapPointer(Vector2(pos.x - SIZE / 2, pos.y + 1), 0, 0, collMap),
			Vector2(pos.x - SIZE / 2, pos.y + 1), 4, collMap, false);

		//真ん中右
		MapJub(MapPointer(Vector2(pos.x + SIZE * 1.5f, pos.y + 1), 0, 0, collMap),
			Vector2(pos.x + SIZE * 1.5f, pos.y + 1), 4, collMap, false);
	}
}

void MapExColl::MapJub(int mapPoint, const Vector2  pos, int XY, int(*collMap)[MAPX], bool flg)
{
	if (flg)
	{
		if (XY == 0)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)(pos.y / SIZE)][(int)((pos.x + 1) / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)(pos.y / SIZE)][(int)((pos.x + 1) / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
		else if (XY == 1)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)(pos.y / SIZE)][(int)((pos.x + SIZE - 1) / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)(pos.y / SIZE)][(int)((pos.x + SIZE - 1) / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
		else if (XY == 2)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)((pos.y + SIZE - 1) / SIZE)][(int)((pos.x + 1) / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)((pos.y + SIZE - 1) / SIZE)][(int)((pos.x + 1) / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
		else if (XY == 3)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)((pos.y + SIZE - 1) / SIZE)][(int)((pos.x + SIZE - 1) / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)((pos.y + SIZE - 1) / SIZE)][(int)((pos.x + SIZE - 1) / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
	}
	else
	{

		if (XY == 0)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)(pos.y / SIZE)][(int)(pos.x / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)(pos.y / SIZE)][(int)(pos.x / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
		else if (XY == 1)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)(pos.y / SIZE)][(int)((pos.x + SIZE * 2) / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)(pos.y / SIZE)][(int)((pos.x + SIZE * 2) / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
		else if (XY == 2)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)((pos.y + SIZE * 2) / SIZE)][(int)(pos.x / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)((pos.y + SIZE * 2) / SIZE)][(int)(pos.x / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
		else if (XY == 3)
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)((pos.y + SIZE * 2) / SIZE)][(int)((pos.x + SIZE * 2) / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)((pos.y + SIZE * 2) / SIZE)][(int)((pos.x + SIZE * 2) / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
		else if ((XY == 4))
		{
			switch (mapPoint)
			{
			case 3:
				collMap[(int)((pos.y) / SIZE)][(int)((pos.x) / SIZE)] = 0;
				break;
			case 40:
				collMap[(int)((pos.y) / SIZE)][(int)((pos.x) / SIZE)] = 41;
				break;
			default:
				break;
			}
		}
	}
}
