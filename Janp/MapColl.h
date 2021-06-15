#pragma once
#include"Draw.h"
class MapColl :public Draw
{
public:
	MapColl();
	~MapColl();
protected:
	int MapPointer(ALLVECTOR allvec, int x, int y, bool flg, std::vector<std::vector<int>>&collMap);
	int MapPointer(ALLVECTOR allvec, int x, int y, bool flg, std::vector<std::vector<int>>& collMap, int&xNum, int&yNum);
	int MapPointerX( int x, int y, std::vector<std::vector<int>>& collMap);
	int MapPointerX( int x, int y, std::vector<std::vector<int>>& collMap, int&xNum, int&yNum);
	int MapPointerY( int x, int y, std::vector<std::vector<int>>& collMap);
	int MapPointerY( int x, int y, std::vector<std::vector<int>>& collMap, int&xNum, int&yNum);
	int MapPointer( int x, int y, std::vector<std::vector<int>>& collMap, int&xNum, int&yNum);
	int MapPointer(Vector2 poss, int x, int y, std::vector<std::vector<int>>& collMap);

};

