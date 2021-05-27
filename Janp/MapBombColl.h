#pragma once
#include "MapColl.h"
class MapBombColl :public MapColl
{
public:
	MapBombColl();
	~MapBombColl();
	void MapColl(int(*collMap)[MAPX],  GameObject& chara, int sizeX, int sizeY, int SizeCut);
private:

	void MapJub(int mapPoint, GameObject& chara, int XY);
};

