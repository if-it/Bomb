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
		const int& maxBomb, const bool& get_guide, const Vector2& playerPos,
		const bool& get_controller_flg, const bool& space_on_flg, int& tutorial_Flg);
	void Draw(const Vector2& sc, const Vector2& shake);

private:
	int heartTex[4];
	int bombTex[5];
	int text_BackTex;
	int key_Z;
	int key_Space;
	int button_X;
	int button_A;
	int tutorial1;

	int backgroundTex;
	int bomb_Ani_Num;
	int heart_Num;
	int max_Heart_Num;
	int bomb_Num;
	int max_Bomb_Num;
	bool bomb_One_Ani;
	bool choice_guide;
	bool choice_guide_flg;
	bool space_guide;
	bool space_guide_flg;
	bool ui_on;
	bool ui_on2;
	int pal;
	bool controller_flg;
	bool tutorial_on;
	int tutorial_flg;

	Animation heart_Ani;
	Animation bomb_Ani;
	Vector2 text_Back_Pos;
	Vector2 tutorial_Size;
};

