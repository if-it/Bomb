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
		const int& maxBomb, const int& get_guide, const Vector2& playerPos,
		const bool& get_controller_flg, const bool& space_on_flg, int& tutorial_Flg,
		const bool&get_move_guide_on,const bool&get_save, int& game_end_set);
	void Draw(const Vector2& sc, const Vector2& shake);

private:
	int heartTex[4];
	int bombTex[5];
	int text_BackTex;
	int key_Z;
	int key_Space;
	int key_Arrow;
	int button_X;
	int button_A;
	int con_LStick;
	int tutorial[3];
	int get_Item_Tex[4];
	int exitTex;


	int backgroundTex;
	int bomb_Ani_Num;
	int heart_Num;
	int max_Heart_Num;
	int bomb_Num;
	int choice_guide;
	int get_Item_guide;
	int max_Bomb_Num;
	int tutorial_flg;
	int tutorial_flg2;
	int tutorial_Pal;
	int pal;
	int get_item_Pal;
	int get_Item_Rand;
	int save_flg;

	bool bomb_One_Ani;
	bool choice_guide_flg;
	bool space_guide;
	bool space_guide_flg;
	bool ui_on;
	bool ui_on2;
	bool controller_flg;
	bool tutorial_on;
	bool tutorial_on2;
	bool get_Item_on;
	bool get_Item_end;
	bool blinking;
	bool move_guide_on;
	bool move_guide;
	bool end_on;

	Animation heart_Ani;
	Animation bomb_Ani;
	Vector2 text_Back_Pos;
	Vector2 guide_Size;
	Vector2 tutorial_Size;
	Vector2 get_item_Size;
	Vector2 exit_Size;

	Count get_Item_Count;
	Count blinking_Count;
};

