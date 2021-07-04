#include "UI.h"

UI::UI()
{
	heartNum = 0;
	bombNum = 0;
	heartTex = 0;
	bombTex = 0;
}

UI::~UI()
{
}

void UI::Init()
{
	heartNum = 0;
	bombNum = 0;
}

void UI::Loading(Load* load)
{
	load->LoadTex("Load/Texture/UI/HeartUI.png", heartTex);
	load->LoadTex("Load/Texture/UI/BombUI.png", bombTex);
}

void UI::Update(const int& hp, const int& playerBomb)
{
	heartNum = hp;
	bombNum = playerBomb;
}

void UI::Draw()
{
	for (int i = 0; i < heartNum; ++i)
	{
		DrawTex(Vector2(16 * i, 16), heartTex, true);
	}
	for (int i = 0; i < bombNum; ++i)
	{
		DrawTex(Vector2(16 * i, 32), bombTex, true);
	}
}
