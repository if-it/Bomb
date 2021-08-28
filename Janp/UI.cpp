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
	ui_on2 = false;
	tutorial_on = false;
	tutorial_flg = 0;
	tutorial_Size = Vector2(0.0f, 0.0f);
}

void UI::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/UI/HeartUI.png", 4, 4, 1, SIZE, SIZE, heartTex);
	load->LoadAnimeTex("Load/Texture/UI/BombUI.png", 5, 5, 1, SIZE, SIZE, bombTex);
	load->LoadTex("Load/Texture/UI/UI_Background.png", backgroundTex);
	load->LoadTex("Load/Texture/UI/text_backUI.png", text_BackTex);

	load->LoadTex("Load/Texture/UI/Key_Z.png", key_Z);
	load->LoadTex("Load/Texture/UI/Key_Space.png", key_Space);

	load->LoadTex("Load/Texture/UI/Button_X.png", button_X);
	load->LoadTex("Load/Texture/UI/Button_A.png", button_A);


	load->LoadTex("Load/Texture/UI/Tutorial1.png", tutorial1);
}

void UI::Update(const int& hp, const int& playerBomb, const int& maxHp,
	const int& maxBomb, const bool& get_guide, const Vector2& playerPos,
	const bool& get_controller_flg, const bool& space_on_flg, int& Get_Tutorial_Flg)
{
	text_Back_Pos = Vector2(playerPos.x, playerPos.y - SIZE - 10);
	max_Heart_Num = maxHp;
	heart_Num = hp;
	bomb_Num = playerBomb;
	max_Bomb_Num = maxBomb;
	controller_flg = get_controller_flg;
	tutorial_flg = Get_Tutorial_Flg;


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
		ui_on2 = true;
	}

	tutorial_on = false;
	if (tutorial_flg > 0)
	{
		tutorial_on = true;
	}
	const int PAL = 9;
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
	/*else
	{
		pal -= PAL;
		if (pal <= 0)
		{
			pal = 0;
			if (choice_guide_flg)choice_guide_flg = false;
			if (space_guide_flg) space_guide_flg = false;
		}
	}*/



	if (tutorial_on && pal <= 228)
	{
		tutorial_Size.x += 0.13f;
		tutorial_Size.y += 0.01f;
		pal += PAL;

		if (pal >= 228)
		{
			pal = 228;
			tutorial_flg = 10;
		}
		if (tutorial_Size.x >= 1.0f)
		{
			tutorial_Size.x = 1.0f;
			tutorial_Size.y += 0.1f;
			if (tutorial_Size.y >= 1.0f)
			{
				tutorial_Size.y = 1.0f;
			}
		}
	}
	if (!ui_on && !tutorial_on)
	{
		pal -= PAL;
		if (pal <= 0)
		{
			ui_on2 = false;
			if (choice_guide_flg)choice_guide_flg = false;
			if (space_guide_flg) space_guide_flg = false;
			tutorial_flg = 0;
			pal = 0;
		}
	}

	Get_Tutorial_Flg = tutorial_flg;
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	Box(text_Back_Pos, GetColor(0, 0, 0), ui_on2, true, shake, sc, 62, 30);
	DrawTex(text_Back_Pos, text_BackTex, ui_on2, true, shake, sc);
	if (controller_flg)
	{
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), button_X, choice_guide_flg, true, shake, sc);
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), button_A, space_guide_flg, true, shake, sc);
	}
	else
	{
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), key_Z, choice_guide_flg, true, shake, sc);
		DrawTex(Vector2(text_Back_Pos.x + 16, text_Back_Pos.y), key_Space, space_guide_flg, true, shake, sc);
	}

	if (tutorial_on == 1)DrawRotaTex(Vector2(WIDTH / 2, HEIGHT / 2), Vector2(256, 318), tutorial_Size, 0.0f, tutorial1, tutorial_on);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
