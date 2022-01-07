#include "OpeningScene.h"

OpeningScene::OpeningScene()
{
}

OpeningScene::~OpeningScene()
{
	DeleteGraph(castle_Tex);
	DeleteGraph(cloud_Tex);
	DeleteSoundMem(kirameki_SE);
}

void OpeningScene::Init()
{
	opening_Flg = 0;
	count = 0;
	castle_Pos = Vector2();
	cloud_Pos = Vector2(-300, 0);
	cloud_Pos2 = Vector2(-200, HEIGHT);
	cloud_Pos3 = Vector2(-WIDTH - 300, 0);
	cloud_Pos4 = Vector2(-WIDTH - 200, HEIGHT);
	back_Pos = Vector2(0, HEIGHT);
	cloud_Vec = Vector2(1, 0);
	light_Ani = Animation();
	light_Pos = Vector2(880, 480);
	light_Vec = Vector2();
}

void OpeningScene::Loading(Load* load, int* tex, int* back)
{
	light_Tex = tex;
	back_Tex = back;
	load->LoadTex("Load/Texture/Opening/Castle.png", castle_Tex);
	load->LoadTex("Load/Texture/Opening/kumo.png", cloud_Tex);
	load->LoadSound("Load/Sound/SE/kirameki.wav", kirameki_SE);
}

bool OpeningScene::Update()
{
	++count;
	cloud_Vec.x += 0.05f;
	cloud_Pos += cloud_Vec;
	cloud_Pos3 += cloud_Vec;
	if (cloud_Vec.x > 4.0f)
	{
		cloud_Vec.x = 4.0f;
	}
	switch (opening_Flg)
	{
	case 0:
		if (count == 60)
		{
			count = 0;
			++opening_Flg;
			PlaySoundMem(kirameki_SE, DX_PLAYTYPE_BACK);
		}
		break;
	case 1:
		light_Ani.Round_Trip_Animation(1, 5);
		light_Vec.y += 0.03f;
		light_Pos += light_Vec;
		if (light_Pos.y >= 900)
		{
			count = 0;
			++opening_Flg;
			cloud_Vec.y = -light_Vec.y;
		}
		break;
	case 2:
		light_Ani.Round_Trip_Animation(1, 5);
		cloud_Vec.y -= 0.03f;
		cloud_Pos2 += cloud_Vec;
		cloud_Pos4 += cloud_Vec;
		castle_Pos.y += cloud_Vec.y;
		if (castle_Pos.y <= -HEIGHT)
		{
			count = 0;
			++opening_Flg;
		}
		break;
	case 3:
		light_Ani.Round_Trip_Animation(1, 5);
		cloud_Vec.y -= 0.03f;
		cloud_Pos2 += cloud_Vec;
		cloud_Pos4 += cloud_Vec;
		if (count == 30)
		{
			count = 0;
			++opening_Flg;
		}
		break;
	case 4:
		light_Ani.Round_Trip_Animation(1, 5);
		cloud_Vec.y -= 0.03f;
		cloud_Pos2 += cloud_Vec;
		cloud_Pos4 += cloud_Vec;
		back_Pos.y += cloud_Vec.y;
		if (back_Pos.y <= 0)
		{
			back_Pos.y = 0;
			count = 0;
			++opening_Flg;
			light_Vec.y = -cloud_Vec.y;
		}
		break;
	case 5:
		light_Ani.Round_Trip_Animation(1, 5);
		light_Vec.y += 0.03f;
		light_Pos += light_Vec;
		if (light_Pos.y > HEIGHT)
		{
			++opening_Flg;
		}
		break;
	default:
		return true;
		break;
	}
	return false;
}

void OpeningScene::Se_Volume(int volume)
{
	ChangeVolumeSoundMem(volume, kirameki_SE);
}

void OpeningScene::Se_Sound()
{
	PlaySoundMem(kirameki_SE, DX_PLAYTYPE_BACK);
}

void OpeningScene::Draw()
{
	switch (opening_Flg)
	{
	case 0:
		DrawTex(castle_Pos, castle_Tex, true, true);
		DrawTex(cloud_Pos, cloud_Tex, true, true);
		DrawTex(cloud_Pos3, cloud_Tex, true, true);
		break;
	case 1:
	case 2:
	case 3:
		DrawTex(castle_Pos, castle_Tex, true, true);
		DrawTex(cloud_Pos, cloud_Tex, true, true);
		DrawTex(cloud_Pos3, cloud_Tex, true, true);
		DrawTex(cloud_Pos2, cloud_Tex, true, true);
		DrawTex(cloud_Pos4, cloud_Tex, true, true);
		DrawTex(light_Pos, light_Tex[light_Ani.num], true);
		break;
	case 4:
	case 5:
	case 6:
		for (int i = 0; i < 4; ++i)
		{
			DrawTex(back_Pos, back_Tex[i], true);
		}
		DrawTex(cloud_Pos2, cloud_Tex, true, true);
		DrawTex(cloud_Pos4, cloud_Tex, true, true);
		DrawTex(light_Pos, light_Tex[light_Ani.num], true);
		break;
	default:
		break;
	}
}
