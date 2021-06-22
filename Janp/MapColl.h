#pragma once
#include"Draw.h"
#define WALL mapPoint == 1 || (mapPoint >= 3 && mapPoint <= 23) || mapPoint == 40||(mapPoint >= 50 && mapPoint <= 57)
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
	void Map_Coll(std::vector<std::vector<int>>& collMap);
	void MapJub(const int& mapPoint, const int& pointNum);
};

