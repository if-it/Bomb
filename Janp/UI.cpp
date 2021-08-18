#include "UI.h"

UI::UI()
{
	heart_Num = 0;
	bomb_Num = 0;
}

UI::~UI()
{
}

void UI::Init()
{
	heart_Num = 0;
	max_Heart_Num = 0;
	bomb_Num = 0;
	heart_Ani = Animation();
	bomb_Ani = Animation();
	bomb_Ani_Num = 0;
	bomb_One_Ani = false;
	pal = 0;
	choice_guide = false;
	choice_guide_flg = false;
	space_guide = false;
	space_guide_flg = false;
	ui_on = false;
}

void UI::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/UI/HeartUI.png", 4, 4, 1, SIZE, SIZE, heartTex);
	load->LoadAnimeTex("Load/Texture/UI/BombUI.png", 5, 5, 1, SIZE, SIZE, bombTex);
	load->LoadTex("Load/Texture/UI/UI_Background.png", backgroundTex);
	load->LoadTex("Load/Texture/UI/text_backUI.png", text_BackTex);
	load->LoadTex("Load/Texture/UI/Key_Z.png", key_Z);
	load->LoadTex("Load/Texture/UI/Button_X.png", button_X);
}

void UI::Update(const int& hp, const int& playerBomb, const int& maxHp,
	const int& maxBomb, const bool& get_guide, const Vector2& playerPos,
	const bool& get_controller_flg, const bool& space_on_flg)
{
	text_Back_Pos = Vector2(playerPos.x, playerPos.y - SIZE - 10);
	max_Heart_Num = maxHp;
	heart_Num = hp;
	bomb_Num = playerBomb;
	max_Bomb_Num = maxBomb;
	controller_flg = get_controller_flg;


	if (bomb_Ani.num != 0)
	{
		bomb_Ani_Num = 6;
		bomb_One_Ani = false;
	}
	else if (!bomb_One_Ani)
	{
		bomb_Ani_Num = GetRand(400);
		bomb_One_Ani = true;
	}
	heart_Ani.AnimationOn(14, 3);
	bomb_Ani.AnimationOn(bomb_Ani_Num, 4);

	choice_guide = get_guide;
	space_guide = space_on_flg;
	ui_on = false;
	if (choice_guide || space_guide)
	{
		ui_on = true;
	}

	const int PAL = 10;
	if (ui_on && pal <= 128)
	{
		pal += PAL;
		if (choice_guide)choice_guide_flg = true;
		if (space_guide)space_guide_flg = true;
		if (pal >= 128)
		{
			pal = 128;
		}
	}
	else
	{
		pal -= PAL * 2;
		if (pal <= 0)
		{
			pal = 0;
			if (choice_guide_flg)choice_guide_flg = false;
			if (space_guide_flg) space_guide_flg = false;
		}
	}
}

void UI::Draw(const Vector2& sc, const Vector2& shake)
{


	DrawTex(Vector2(16, 16), backgroundTex, true);
	Vector2 pos;
	for (int i = 0; i < max_Heart_Num; ++i)
	{
		pos = Vector2((SIZE + 10) * i + SIZE * 1.5f, 16);

		if (i < heart_Num)DrawTex(pos, heartTex[heart_Ani.num], true);
		else DrawTex(pos, heartTex[3], true);
	}
	for (int i = 0; i < max_Bomb_Num; ++i)
	{
		pos = Vector2((SIZE + 10) * i + SIZE * 1.5f, SIZE * 1.8f);

		if (i < bomb_Num)DrawTex(pos, bombTex[bomb_Ani.num], true);
		else DrawTex(pos, bombTex[4], true);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal / 2);
	Box(text_Back_Pos, GetColor(0, 0, 0), ui_on, true, shake, sc, 62, 30);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	DrawTex(text_Back_Pos, text_BackTex, ui_on, true, shake, sc);
	if (controller_flg)
	{
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), button_X, choice_guide_flg, true, shake, sc);
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), button_X, space_guide_flg, true, shake, sc);
	}
	else
	{
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), key_Z, choice_guide_flg, true, shake, sc);
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), key_Z, space_guide_flg, true, shake, sc);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
