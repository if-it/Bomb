#pragma once
#include"Draw.h"
#include "Load.h"
#define B_MAX_COUNT 5


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
private:
	std::vector<std::vector<int>> bBlockCount;
	std::vector<std::vector<int>> fleMap;

	int tex[10];
	int Btex[10];


	// 0 ��C
	// 1 �u���b�N
	// 2 ��
	// 3 ����u���b�N
	// 4 ���C
	// 5 ����C
	// 6 ����C
	// 7 �E��C
	// 8 �㓱�ΐ�
	// 9 �����ΐ�
	// 10 �����ΐ�
	// 11 �E���ΐ�
	// 12 ����p
	// 13 �E��p
	// 14 �����p
	// 15 �E���p
	// 16 �㍶�p
	// 17 ��E�p
	// 18 �����p
	// 19 ���E�p
	// 20 ��E��
	// 21 �����E
	// 22 ���㉺
	// 23 �E����
	// 24 
	// 40�`49 �����u���b�N

	// 60 ����
	// 61 �����
	// 62 �E���
	// 63 �����



	
};

