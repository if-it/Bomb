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
}

void UI::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/UI/HeartUI.png", 4, 4, 1, SIZE, SIZE, heartTex);
	load->LoadAnimeTex("Load/Texture/UI/BombUI.png", 5, 5, 1, SIZE, SIZE, bombTex);
	load->LoadTex("Load/Texture/UI/UI_Background.png", backgroundTex);
}

void UI::Update(const int& hp, const int& playerBomb, const int& maxHp, const int& maxBomb)
{
	max_Heart_Num = maxHp;
	heart_Num = hp;
	bomb_Num = playerBomb;
	max_Bomb_Num = maxBomb;
	if (bomb_Ani.num != 0)
	{
		bomb_Ani_Num = 6;
		bomb_One_Ani = false;
	}
	else if(!bomb_One_Ani)
	{
		bomb_Ani_Num = GetRand(400);
		bomb_One_Ani = true;
	}
	heart_Ani.AnimationOn(14, 3);
	bomb_Ani.AnimationOn(bomb_Ani_Num, 4);


}

void UI::Draw()
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
}
