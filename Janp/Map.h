#pragma once
#include"Draw.h"
#include "Load.h"
#define B_MAX_COUNT 5
#define MAP_TEX_NUM 22

class Map :public Draw
{
public:
	Map();
	~Map();
	void Save_Date_Load(const int& date_Num, const int& stage);
	void Init(const int& stage);
	void Save_Data_Init(const int& stage);
	void Save(const int& date_Num);
	void StageSet(const int& stage);
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

	struct Save_Date
	{
		int data;
		int data2;
	};
	Save_Date save_Data;
};

