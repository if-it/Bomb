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
	void Update(const int& hp, const int& playerBomb, const int& maxHp, 
		const int& maxBomb,const bool&get_guide,const Vector2& playerPos);
	void Draw(const Vector2& sc, const Vector2& shake);

private:
	int heartTex[4];
	int bombTex[5];
	int text_BackTex;

	int backgroundTex;
	int bomb_Ani_Num;
	int heart_Num;
	int max_Heart_Num;
	int bomb_Num;
	int max_Bomb_Num;
	bool bomb_One_Ani;
	bool guide;

	Animation heart_Ani;
	Animation bomb_Ani;
	Vector2 text_Back_Pos;
};

