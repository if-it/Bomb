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
	choice_guide = -1;
	guide_Size = Vector2(0.0f, 0.1f);
	choice_guide_flg = false;
	space_guide = false;
	space_guide_flg = false;
	ui_on = false;
	ui_on2 = false;
	tutorial_on = false;
	tutorial_on2 = false;
	tutorial_flg = 0;
	tutorial_flg2 = 0;
	tutorial_Size = Vector2();
	get_item_Pal = 0;
	get_item_Size = Vector2();
	get_Item_Count = Count();
	blinking_Count = Count();
	get_Item_guide = 0;
	get_Item_end = false;
	get_Item_on = false;
	blinking = false;
	get_Item_Rand = 0;
	move_guide_on = false;
	move_guide = false;
	save_flg = 0;
	exit_Size = Vector2(0.0f, 0.01f);
}

void UI::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/UI/HeartUI.png", 4, 4, 1, SIZE, SIZE, heartTex);
	load->LoadAnimeTex("Load/Texture/UI/BombUI.png", 5, 5, 1, SIZE, SIZE, bombTex);
	load->LoadTex("Load/Texture/UI/UI_Background.png", backgroundTex);
	load->LoadTex("Load/Texture/UI/text_backUI.png", text_BackTex);

	load->LoadTex("Load/Texture/UI/Key_Z.png", key_Z);
	load->LoadTex("Load/Texture/UI/Key_Space.png", key_Space);
	load->LoadTex("Load/Texture/UI/Key_Arrow.png", key_Arrow);

	load->LoadTex("Load/Texture/UI/Button_X.png", button_X);
	load->LoadTex("Load/Texture/UI/Button_A.png", button_A);
	load->LoadTex("Load/Texture/UI/LStick.png", con_LStick);


	load->LoadTex("Load/Texture/UI/Tutorial1.png", tutorial[0]);
	load->LoadTex("Load/Texture/UI/Tutorial2.png", tutorial[1]);
	load->LoadTex("Load/Texture/UI/Tutorial3.png", tutorial[2]);


	load->LoadTex("Load/Texture/UI/GetBomb.png", get_Item_Tex[0]);
	load->LoadTex("Load/Texture/UI/HpUP.png", get_Item_Tex[1]);
	load->LoadTex("Load/Texture/UI/AttackUP.png", get_Item_Tex[2]);
	load->LoadTex("Load/Texture/UI/Save.png", get_Item_Tex[3]);

	load->LoadTex("Load/Texture/UI/Exit.png", exitTex);
}

void UI::Update(const int& hp, const int& playerBomb, const int& maxHp,
	const int& maxBomb, const int& get_guide, const Vector2& playerPos,
	const bool& get_controller_flg, const bool& space_on_flg, int& Get_Tutorial_Flg,
	const bool& get_move_guide_on, const bool& get_save, int& game_end_set)
{
	text_Back_Pos = Vector2(playerPos.x, playerPos.y - SIZE - 10);
	max_Heart_Num = maxHp;
	heart_Num = hp;
	bomb_Num = playerBomb;
	max_Bomb_Num = maxBomb;
	controller_flg = get_controller_flg;
	tutorial_flg = Get_Tutorial_Flg;
	choice_guide = get_guide;
	space_guide = space_on_flg;
	move_guide_on = get_move_guide_on;

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

	//SaveUI
	if (get_save)
	{
		save_flg = 1;
	}
	else if (save_flg == 1)
	{
		save_flg = 2;
	}

	heart_Ani.AnimationOn(14, 3);
	bomb_Ani.AnimationOn(bomb_Ani_Num, 4);

	ui_on = false;
	if (choice_guide == 0 || space_guide || move_guide_on)
	{
		ui_on = true;
		ui_on2 = true;
	}

	tutorial_on = false;
	if (tutorial_flg > 0)
	{
		tutorial_on = true;
		if (!tutorial_on2)
		{
			tutorial_on2 = true;
			tutorial_flg2 = tutorial_flg;
		}
	}
	const int PAL = 9;

	//ガイドUI
	if (ui_on && pal <= 128)
	{
		pal += PAL;
		guide_Size.x += 0.2f;
		if (guide_Size.x >= 1.0f)
		{
			guide_Size.x = 1.0f;
			guide_Size.y += 0.2f;
			if (guide_Size.y >= 1.0f)
			{
				guide_Size.y = 1.0f;
			}
		}
		if (choice_guide == 0)choice_guide_flg = true;
		if (space_guide)space_guide_flg = true;
		if (move_guide_on)move_guide = true;
		if (pal >= 128)
		{
			pal = 128;
		}

	}
	if (!ui_on)
	{
		pal -= 3;
		guide_Size.y -= 0.2f;
		guide_Size.x -= 0.01f;
		if (guide_Size.y <= 0.1f)
		{
			guide_Size.y = 0.1f;
			guide_Size.x -= 0.2f;
			if (guide_Size.x < 0.0f)
			{
				guide_Size = Vector2();
				ui_on2 = false;
				choice_guide_flg = false;
				space_guide_flg = false;
				move_guide = false;
				pal = 0;
				guide_Size = Vector2(0.0f, 0.1f);
			}
		}
	}
	//アイテムGetUI
	if (choice_guide > 0 || get_Item_on || save_flg == 2)
	{
		if (!get_Item_on)
		{
			get_Item_on = true;
			blinking_Count.flg = true;
			if (save_flg != 2)get_Item_guide = choice_guide;
			get_Item_Rand = GetRand(3) + 2;
		}
		if (!get_Item_end)
		{
			get_item_Pal += PAL;
			get_item_Size.x += 0.1f;
			get_item_Size.y += 0.01f;
			if (get_item_Size.x >= 1.0f)
			{
				get_item_Size.x = 1.0f;
				get_item_Size.y += 0.06f;
				if (get_item_Size.y >= 1.0f)
				{
					get_item_Size.y = 1.0f;
					blinking_Count = Count();
					get_Item_Count.flg = true;
					blinking_Count.flg = true;
					blinking = true;
				}
			}
			if (blinking_Count.Conuter(get_Item_Rand))
			{
				get_Item_Rand = GetRand(3) + 2;
				blinking_Count.flg = true;

				if (blinking)blinking = false;
				else blinking = true;
			}
			if (get_item_Pal >= 228)
			{
				get_item_Pal = 228;
			}
			if (get_Item_Count.Conuter(80))
			{
				get_Item_Count = Count();
				get_Item_Count.flg = true;
				get_Item_end = true;
			}
		}
		else
		{
			get_item_Pal -= PAL;
			get_item_Size.y -= 0.1f;
			get_item_Size.x -= 0.01f;
			if (get_item_Size.y <= 0.1f)
			{
				get_item_Size.y = 0.1f;
				get_item_Size.x -= 0.1f;
				if (get_item_Size.x < 0.0f)
				{
					get_item_Size = Vector2();
				}
			}
			if (get_item_Pal <= 0)
			{
				get_item_Pal = 0;
				get_Item_end = false;
				get_Item_on = false;
				get_Item_guide = -1;
				blinking_Count = Count();
				get_item_Size = Vector2();
				save_flg = 0;
			}
		}

	}

	//能力GetチュートリアルUI
	if (tutorial_on && tutorial_Pal <= 228)
	{
		tutorial_Size.x += 0.13f;
		tutorial_Size.y += 0.01f;
		tutorial_Pal += PAL;

		if (tutorial_Pal >= 228)
		{
			tutorial_Pal = 228;
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
	if (!tutorial_on)
	{
		tutorial_Pal -= 3;
		tutorial_Size.y -= 0.15f;
		if (tutorial_Size.y <= 0.02f)
		{
			tutorial_Size.y = 0.02f;
			tutorial_Size.x -= 0.15f;
			if (tutorial_Size.x <= 0.0f)
			{
				tutorial_Size = Vector2();
				tutorial_flg = 0;
				tutorial_Pal = 0;
				tutorial_on2 = false;
				tutorial_flg2 = 0;
			}
		}
	}


	//ExitUI

	Exit(game_end_set);



	Get_Tutorial_Flg = tutorial_flg;
}

void UI::Exit(int& game_end_set)
{
	if (game_end_set == 1)
	{
		end_on = true;
		exit_Size.x += 0.07f;
		if (exit_Size.x >= 1.0f)
		{
			exit_Size.x = 1.0f;
			exit_Size.y += 0.06f;
			if (exit_Size.y)
			{
				exit_Size.y = 1.0f;
				game_end_set = 2;
			}
		}
	}
	if (game_end_set == 4)
	{
		exit_Size.y -= 0.1f;
		if (exit_Size.y <= 0.01f)
		{
			exit_Size.y = 0.01f;
			exit_Size.x -= 0.1f;
			if (exit_Size.x <= 0)
			{
				exit_Size.x = 0;
				game_end_set = 0;
			}
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	Vector2 guide_Pos = Vector2(text_Back_Pos.x + 32, text_Back_Pos.y + 16);
	DrawRotaTex(guide_Pos, Vector2(32, 16), guide_Size, 0.0f, text_BackTex, ui_on2, false, true, shake, sc);
	if (controller_flg)
	{
		DrawRotaTex(Vector2(guide_Pos.x, guide_Pos.y), Vector2(16, 16), guide_Size, 0.0f, button_X, choice_guide_flg, false, true, shake, sc);
		DrawRotaTex(Vector2(guide_Pos.x, guide_Pos.y), Vector2(16, 16), guide_Size, 0.0f, button_A, space_guide_flg, false, true, shake, sc);
		DrawRotaTex(Vector2(guide_Pos.x, guide_Pos.y), Vector2(32, 16), guide_Size, 0.0f, con_LStick, move_guide, false, true, shake, sc);
	}
	else
	{
		DrawRotaTex(Vector2(guide_Pos.x, guide_Pos.y), Vector2(16, 16), guide_Size, 0.0f, key_Z, choice_guide_flg, false, true, shake, sc);
		DrawRotaTex(Vector2(guide_Pos.x, guide_Pos.y), Vector2(16, 16), guide_Size, 0.0f, key_Space, space_guide_flg, false, true, shake, sc);
		DrawRotaTex(Vector2(guide_Pos.x, guide_Pos.y), Vector2(32, 16), guide_Size, 0.0f, key_Arrow, move_guide, false, true, shake, sc);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, tutorial_Pal);
	if (tutorial_flg2 == 1)DrawRotaTex(Vector2(WIDTH / 2, HEIGHT / 2), Vector2(256, 318), tutorial_Size, 0.0f, tutorial[0], tutorial_on2);
	if (tutorial_flg2 == 2)DrawRotaTex(Vector2(WIDTH / 2, HEIGHT / 2), Vector2(256, 318), tutorial_Size, 0.0f, tutorial[1], tutorial_on2);
	if (tutorial_flg2 == 3)DrawRotaTex(Vector2(WIDTH / 2, HEIGHT / 2), Vector2(256, 318), tutorial_Size, 0.0f, tutorial[2], tutorial_on2);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, get_item_Pal);
	if (blinking)
	{
		Vector2 get_Item_Pos = Vector2(text_Back_Pos.x + 32, text_Back_Pos.y + 16);
		if (get_Item_guide == 1)
		{
			DrawRotaTex(get_Item_Pos, Vector2(64, 16), get_item_Size, 0.0f, get_Item_Tex[0], get_Item_on, false, true, shake, sc);
		}
		if (get_Item_guide == 2)
		{
			DrawRotaTex(get_Item_Pos, Vector2(64, 16), get_item_Size, 0.0f, get_Item_Tex[1], get_Item_on, false, true, shake, sc);
		}
		if (get_Item_guide == 4)
		{
			DrawRotaTex(get_Item_Pos, Vector2(64, 16), get_item_Size, 0.0f, get_Item_Tex[2], get_Item_on, false, true, shake, sc);
		}
		if (save_flg == 2)
		{
			DrawRotaTex(get_Item_Pos, Vector2(64, 16), get_item_Size, 0.0f, get_Item_Tex[3], get_Item_on, false, true, shake, sc);
		}
	}
	ExitDraw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void UI::ExitDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 228);
	DrawRotaTex(Vector2(WIDTH / 2, HEIGHT / 2), Vector2(256, 128), exit_Size, 0.0f, exitTex, end_on);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
