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
		filename += "Taiin";
		filename += to_string(talk_Scene%100);
		filename += ".csv";
		reading_file.open(filename, ios::in);
		break;
	default:
		break;
	}
	if (!reading_file)
	{
		MessageBox(NULL, "Text", "Textファイルのエラー", MB_OK);
		return;
	}

	int lineI = 0;
	string load_file;

	stringstream  ss;
	string key;
	while (getline(reading_file, load_file))
	{
		int lineN = 0;
		ss = stringstream(load_file);
		texts.push_back(std::vector<int>());
		text_obj.push_back(std::vector<GameObject>());

		while (getline(ss, key, ','))
		{
			ss >> lineN;
			texts[lineI].push_back(lineN);
			text_obj[lineI].push_back(GameObject());
		}
		++lineI;
	}
	reading_file.close();
	for (int i = 0; i < (int)texts.size(); ++i)
	{
		for (int n = 0; n < (int)texts[i].size(); ++n)
		{
			text_obj[i][n].SetPos(Vector2(WIDTH / 2 - 550 + SIZE * n, HEIGHT / 2 + 320 + SIZE * i));
		}
	}
}

void Text::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/font.png", TEX_MAX_NUM, 5, 69, 32, 32, tex);
}

void Text::Update(int& talk_Scene, Controller* con)
{
}

void Text::Draw()
{
	Box(Vector2(WIDTH / 2 - 600, HEIGHT / 2 + 300), GetColor(0, 0, 0), true, true, Vector2(), Vector2(), 1200, 200);
	for (int i = 0; i < (int)texts.size(); ++i)
	{
		for (int n = 0; n < (int)texts[i].size(); ++n)
		{
			int a = texts[i][n];
			DrawTex(text_obj[i][n], tex[a]);
		}
	}
}
