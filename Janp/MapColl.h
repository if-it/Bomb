#pragma once
#include"Draw.h"
class MapColl :public Draw
{
public:
	MapColl();
	~MapColl();
protected:
	int MapPointer(ALLVECTOR allvec, int x, int y, bool flg, int(*collMap)[MAPX]);
	int MapPointer(ALLVECTOR allvec, int x, int y, bool flg, int(*collMap)[MAPX], int&xNum, int&yNum);
	int MapPointerX( int x, int y, int(*collMap)[MAPX]);
	int MapPointerX( int x, int y, int(*collMap)[MAPX], int&xNum, int&yNum);
	int MapPointerY( int x, int y, int(*collMap)[MAPX]);
	int MapPointerY( int x, int y, int(*collMap)[MAPX], int&xNum, int&yNum);
	int MapPointer( int x, int y, int(*collMap)[MAPX], int&xNum, int&yNum);
	int MapPointer(Vector2 poss, int x, int y, int(*collMap)[MAPX]);

};

