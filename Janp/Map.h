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
	void Save_Date_Load(const int& date_Num, const int& stage, Load* load);
	void Init(const int& stage, Load* load);
	void Save_Data_Init();
	void Save(const int& data_Num);
	void StageSet(const int& stage, Load* load);
	void Loading(Load* load);
	void FleMapInput();
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
	void FrontDraw(const Vector2& sc, const Vector2& shake);

	std::vector<std::vector<int>> map;

	int* Get_Map_Tex() { return tex; }
private:
	std::vector<std::vector<int>> bBlockCount;
	std::vector<std::vector<int>> fleMap;

	int tex[MAP_TEX_NUM];
	int Btex[10];
	int togeTex[4];
	int save_Data_Size;
	int stage_S;
	int pal;
	int pal_Flg;
	bool front_Draw;
	struct Save_Data
	{
		int stage;
		int map_num_X;
		int map_num_Y;
		int map_num;
	};
	std::vector<Save_Data> save_Data_Ori;
};

