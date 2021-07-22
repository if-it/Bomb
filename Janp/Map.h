#pragma once
#include"Draw.h"
#include "Load.h"
#define B_MAX_COUNT 5
#define MAP_TEX_NUM 16

class Map :public Draw
{
public:
	Map();
	~Map();
	void Init(int stage);
	void StageSet(int stage);
	void Loading(Load* load);
	void FleMapInput();
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
	//int map[MAPY][MAPX];
	std::vector<std::vector<int>> map;

	int* Get_Map_Tex() { return tex; }
private:
	std::vector<std::vector<int>> bBlockCount;
	std::vector<std::vector<int>> fleMap;

	int tex[MAP_TEX_NUM];
	int Btex[10];


	
};

