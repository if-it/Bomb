#pragma once
#include "Draw.h"
#include "Load.h"
class UI : public Draw
{
public:
	UI();
	~UI();
	void Init();
	void Loading(Load* load);
	void Update(const int& hp, const int& playerBomb, const int& maxHp, const int& maxBomb);
	void Draw();

private:
	int heartTex[4];
	int bombTex[5];
	int backgroundTex;
	int bomb_Ani_Num;
	int heart_Num;
	int max_Heart_Num;
	int bomb_Num;
	int max_Bomb_Num;
	bool bomb_One_Ani;

	Animation heart_Ani;
	Animation bomb_Ani;
};

