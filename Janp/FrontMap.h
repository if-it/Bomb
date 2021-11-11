#pragma once
#include "Draw.h"
#include"Load.h"
#define FRONT_MAP1 10
#define FRONT_MAP2 10
#define FRONT_MAP3 10

class FrontMap :
	public Draw
{
public:
	FrontMap();
	~FrontMap();
	void Init(const int& stage, Load* load);
	void Loading(Load* load);
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
private:
	std::vector<std::vector<int>> frontMap;
	int*  through_Tex;//‚·‚è”²‚¯•Ç

	int texArray;
	int stage_S;
	int guide[20];
	Animation guide_ani;
	bool guide_Flg;
};

