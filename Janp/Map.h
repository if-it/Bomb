#pragma once
#include"Draw.h"
#define B_MAX_COUNT 5


class Map :public Draw
{
public:
	Map();
	~Map();
	void Init(int stage);
	void StageSet(int stage);
	void FleMapInput();
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
	//int map[MAPY][MAPX];
	int tex[10];
	std::vector<std::vector<int>> map;
	int Btex[10];
private:
	std::vector<std::vector<int>> bBlockCount;
	std::vector<std::vector<int>> fleMap;

	// 0 空気
	// 1 ブロック
	// 2 黒
	// 3 壊れるブロック
	// 4 上大砲
	// 5 下大砲
	// 6 左大砲
	// 7 右大砲
	// 8 上導火線
	// 9 下導火線
	// 10 左導火線
	// 11 右導火線
	// 12 左上角
	// 13 右上角
	// 14 左下角
	// 15 右下角
	// 16 上左角
	// 17 上右角
	// 18 下左角
	// 19 下右角
	// 20 上右左
	// 21 下左右
	// 22 左上下
	// 23 右下上
	// 24 
	// 40～49 復元ブロック

	// 60 上矢印
	// 61 下矢印
	// 62 右矢印
	// 63 左矢印



	
};

