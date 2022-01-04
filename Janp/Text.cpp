#include "Text.h"
#include<fstream>
#include<sstream>

Text::Text()
{
}

Text::~Text()
{
}

void Text::Init(int& talk_Scene)
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
		text_obj[i].SetPos(Vector2(WIDTH / 2 - 350 + SIZE * x_num, HEIGHT / 2 + 320 + (SIZE + 10) * y_num));
		++x_num;
	}

	count = 0;
	now_Num = 0;
	talk_Flg = 0;
	next = talk_Scene;
	end = false;
}

void Text::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/font.png", TEX_MAX_NUM, 5, 69, 32, 32, tex);
}

void Text::Update(int& talk_Scene, bool enter)
{
	switch (talk_Flg)
	{
	case 0:
		++count;
		if (count == 5)
		{
			count = 0;
			text_obj[now_Num].game.dis = true;
			++now_Num;
			if (now_Num >= texts.size())
			{
				now_Num = 0;
				talk_Flg = 2;
			}
		}
		if (enter)
		{
			talk_Flg = 1;
		}
		break;

	case 1:
		for (int i = 0; i < (int)texts.size(); ++i)
		{
			text_obj[i].game.dis = true;
		}
		talk_Flg = 2;
		break;
	case 2:
		if (enter)talk_Flg = 3;
		break;
	case 3:
		switch (talk_Scene)
		{
		case 100:
			++talk_Scene;
			break;
		default:
			break;
		}
		if (next != talk_Scene)
		{
			Init(talk_Scene);
		}
		else
		{
			end = true;
			texts.clear();
			text_obj.clear();
		}
		break;
	default:
		break;
	}





}

void Text::Draw()
{
	Box(Vector2(WIDTH / 2 - 600, HEIGHT / 2 + 300), GetColor(0, 0, 0), true, true, Vector2(), Vector2(), 1200, 200);
	Box(Vector2(WIDTH / 2 - 600, HEIGHT / 2 + 250), GetColor(255, 0, 0), true, true, Vector2(), Vector2(), 200, 250);
	for (int i = 0; i < (int)texts.size(); ++i)
	{
		DrawTex(text_obj[i], tex[texts[i]]);
	}
}
