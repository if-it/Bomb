#include "Text.h"
#include<fstream>
#include<sstream>

Text::Text()
{
	game_object.game.pal = 0;
}

Text::~Text()
{
}

void Text::Init(int& talk_Scene, Load* load)
{
	using namespace std;

	texts.clear();
	text_obj.clear();

	int name = (int)(talk_Scene / 100);
	ifstream reading_file;
	string filename = "Data/Text/";
	switch (name)
	{
	case 1:
		filename += "Taiin/Taiin";
		load->LoadAnimeTex("Load/Texture/Chara/Taiin.png", 2, 2, 1, 200, 250, chara_Tex);
		load->LoadSound("Load/Sound/SE/Taiin.wav", voice);
		break;
	default:
		break;
	}
	filename += to_string(talk_Scene % 100);
	filename += ".csv";
	reading_file.open(filename, ios::in);
	if (!reading_file)
	{
		MessageBox(NULL, "Text", "Textファイルのエラー", MB_OK);
		return;
	}

	string load_file;

	stringstream  ss;
	string key;

	int lineN = 0;
	getline(reading_file, load_file);
	ss = stringstream(load_file);
	while (getline(ss, key, ','))
	{
		ss >> lineN;
		texts.push_back(lineN);
		text_obj.push_back(GameObject("", false));
	}

	reading_file.close();

	int y_num = 0;
	int x_num = 0;
	for (int i = 0; i < (int)texts.size(); ++i)
	{
		if (texts[i] == 279)
		{
			++y_num;
			x_num = -1;
		}
		text_obj[i].SetPos(Vector2(WIDTH / 2 - 350 + SIZE * x_num, HEIGHT / 2 + 350 + (SIZE + 10) * y_num));
		++x_num;
	}

	count = 0;
	count2 = 0;
	now_Num = 0;
	talk_Flg = 0;
	next = talk_Scene;
	end = false;
	enter_Flg = false;
	enter_Pos = Vector2(WIDTH / 2 - 24, HEIGHT / 2 + 450);
	animation[0] = 30;
	animation[1] = 5;
	ani = Animation();
	enter_Pos2[0] = enter_Pos;
	enter_Pos2[1] = enter_Pos;
	enter_Pos2[1].y += 10;
	enter_Move = false;
	dis = true;
}

void Text::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/font.png", TEX_MAX_NUM, 5, 69, 32, 32, text_Tex);
	load->LoadAnimeTex("Load/Texture//UI/Text_Next.png", 2, 2, 1, 48, 48, text_Next_Tex);
	load->LoadTex("Load/Texture/UI/Text_back.png", text_Back_Tex);
}

void Text::Update(int& talk_Scene, bool enter, Load* load, const bool& get_controller_flg)
{
	con_Flg = (int)get_controller_flg;
	enter_Flg = enter;
	if (enter_Flg)enter_Count.flg = true;

	enter_Count.Counter(20);
	ani.AnimationOn(animation[ani.num], 2);
	if (ani.num == 1)
	{
		animation[0] = GetRand(250) + 10;
	}
	++count2;
	if (count2 == 30)
	{
		count2 = 0;
		if (enter_Move)	enter_Move = false;
		else enter_Move = true;
		enter_Pos = enter_Pos2[(int)enter_Move];
	}


	switch (talk_Flg)
	{
	case 0:
		game_object.game.pal += 20;
		if (game_object.game.pal >= 255)
		{
			game_object.game.pal = 255;
			talk_Flg = 1;
		}
		break;
	case 1:
		++count;
		if (count == 8)
		{
			if (texts[now_Num] != 279)PlaySoundMem(voice, DX_PLAYTYPE_BACK);

			count = 0;
			text_obj[now_Num].game.dis = true;
			++now_Num;
			if (now_Num >= texts.size())
			{
				now_Num = 0;
				talk_Flg = 3;
			}
		}
		if (enter_Flg)
		{
			talk_Flg = 2;
		}
		break;

	case 2:
		for (int i = 0; i < (int)texts.size(); ++i)
		{
			text_obj[i].game.dis = true;
		}
		talk_Flg = 3;
		break;
	case 3:
		if (enter_Flg)talk_Flg = 4;
		break;
	case 4:
		switch (talk_Scene)
		{
		case 100:
		case 101:
			++talk_Scene;
			break;
		default:
			break;
		}
		if (next != talk_Scene)
		{
			Init(talk_Scene, load);
		}
		else
		{
			talk_Flg = 5;
		}
		break;
	case 5:
		game_object.game.pal -= 20;
		if (game_object.game.pal <= 0)
		{
			end = true;
			con_Flg = 0;
			enter_Count = Count();
			texts.clear();
			text_obj.clear();
			DeleteGraph(chara_Tex[0]);
			DeleteGraph(chara_Tex[1]);
			game_object.game.pal = 0;
			DeleteSoundMem(voice);
			dis = false;
		}
		break;
	default:
		break;
	}





}

void Text::Se_Volume(int volume)
{
	ChangeVolumeSoundMem(volume, voice);
}

void Text::Draw()
{
	if (dis)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, game_object.game.pal);
		//Box(Vector2(WIDTH / 2 - 600, HEIGHT / 2 + 300), GetColor(0, 0, 0), true, true, Vector2(), Vector2(), 1200, 200);
		DrawTex(Vector2(WIDTH / 2 - 600, HEIGHT / 2 + 300), text_Back_Tex, true);
		//Box(Vector2(WIDTH / 2 - 600, HEIGHT / 2 + 250), GetColor(255, 0, 0), true, true, Vector2(), Vector2(), 200, 250);
		DrawTex(Vector2(WIDTH / 2 - 600, HEIGHT / 2 + 250), chara_Tex[ani.num], true);
		DrawTex(enter_Pos, text_Next_Tex[con_Flg], true);
		if (enter_Count.flg)
		{
			SetBright(COLOR(150, 150, 150));
			DrawTex(enter_Pos, text_Next_Tex[con_Flg], true);
			SetBright();
		}
		for (int i = 0; i < (int)texts.size(); ++i)
		{
			DrawTex(text_obj[i], text_Tex[texts[i]]);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
