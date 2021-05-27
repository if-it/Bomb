#pragma once
#include "MapColl.h"
class MapExColl:public MapColl
{
public:
	MapExColl();
	~MapExColl();
	void MapColl(int(*collMap)[MAPX],const Vector2& pos, int sizeX, int sizeY, int SizeCut,bool flg);
private:
	void MapJub(int mapPoint,const Vector2 pos, int XY, int(*collMap)[MAPX],bool flg );
	int bxNum[8];
	int byNum[8];

};

