#include "BackMap2.h"
#include<fstream>
#include<sstream>

BackMap2::BackMap2()
{
}

BackMap2::~BackMap2()
{
}

void BackMap2::Init(const int& stage)
{

	for (int i = 0; i < 5; ++i)
	{
		back_Pos[i] = Vector2(0, -HEIGHT);
		back_Pos2[i] = Vector2(WIDTH * 2, -HEIGHT);
		back_Sc[i] = Vector2();
		back_Sc2[i] = Vector2();
		back_count[i] = 0;
		back_count2[i] = 0;
	}

	using namespace std;

	backMap.clear();

	ifstream ifs;
	string fileNama;


	switch (stage)
	{
	case 0:
		fileNama = "Load/Data/Map/BackMap2/Bomb_BackMap2 - demo.csv";
		break;
	case 100:
		//fileNama = "Load/Data/Map/BackMap2/Bomb_BackMap2 - Stage100.csv";
		break;
	case 200:
		//fileNama = "Load/Data/Map/BackMap2/Bomb_BackMap2 - Stage200.csv";
		break;
	default:
		fileNama = "Load/Data/Map/BackMap2/Bomb_BackMap - demo.csv";
		break;
	}

	ifs.open(fileNama.c_str());
	if (!ifs)
	{
		MessageBox(NULL, "BackMap", "MapData2‚ÌƒGƒ‰[", MB_OK);

		return;
	}

	string line;
	int mapNum = 0;
	istringstream ss;
	string key;
	while (getline(ifs, line))
	{
		int lineN = 0;
		ss = istringstream(line);
		backMap.push_back(std::vector<int>());
		int i = 0;
		while (getline(ss, key, ','))
		{
			ss >> lineN;
			backMap[mapNum].push_back(lineN);
		}
		++mapNum;
	}

	ifs.close();


}

void BackMap2::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/BackMap2/BackMap.png", BACKMAP2_TEX_NUM, BACKMAP2_TEX_NUM, 1, SIZE, SIZE, tex);
	load->LoadTex("Load/Texture/Map/BackObj/Stage200Back1.png", stage2_Back_Tex[4]);
	load->LoadTex("Load/Texture/Map/BackObj/Stage200Back2.png", stage2_Back_Tex[3]);
	load->LoadTex("Load/Texture/Map/BackObj/Stage200Back3.png", stage2_Back_Tex[2]);
	load->LoadTex("Load/Texture/Map/BackObj/Stage200Back4.png", stage2_Back_Tex[1]);
	load->LoadTex("Load/Texture/Map/BackObj/Stage200Back5.png", stage2_Back_Tex[0]);
}

void BackMap2::Update(const Vector2& sc)
{
	for (int i = 0; i < 5; ++i)
	{
		back_Sc[i] = Vector2(sc.x / (2 * (6 - (i + 1))), 0);
		back_Sc2[i] = Vector2(sc.x / (2 * (6 - (i + 1))), 0);

		if (back_Sc[i].x >= WIDTH * 2 * (back_count[i] + 1))
		{
			back_Pos[i].x += WIDTH * 4 * (back_count[i] + 1);
			++back_count[i];
		}
		if (back_Sc[i].x <= -WIDTH * 2 * (back_count[i] + 1))
		{
			back_Pos[i].x += -WIDTH * 4 * (back_count[i] + 1);
			--back_count[i];
			if (back_count[i] <= 0)
			{
				back_count[i] = 0;
			}
		}
		if (back_Sc2[i].x >= WIDTH * 4 * (back_count2[i] + 1))
		{
			back_Pos2[i].x += WIDTH * 8 * (back_count2[i] + 1);
			++back_count2[i];
		}
		if (back_Sc2[i].x <= -WIDTH * 4 * (back_count2[i] + 1))
		{
			back_Pos2[i].x += -WIDTH * 8 * (back_count2[i] + 1);
			--back_count2[i];
			if (back_count2[i] <= 0)
			{
				back_count2[i] = 0;
			}
		}
	}
}

void BackMap2::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < 5; ++i)
	{
		DrawTex(back_Pos[i], stage2_Back_Tex[i], true, true, Vector2(), back_Sc[i]);
		DrawTex(back_Pos2[i], stage2_Back_Tex[i], true, true, Vector2(), back_Sc2[i]);
	}
	for (int y = 0; y < (int)backMap.size(); ++y)
	{
		for (int x = 0; x < (int)backMap[y].size(); ++x)
		{
			switch (backMap[y][x])
			{
			case 1:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[0], true, true, shake, sc);
				break;
			case 2:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[1], true, true, shake, sc);
				break;
			case 3:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[2], true, true, shake, sc);
				break;
			case 4:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[3], true, true, shake, sc);
				break;
			case 5:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[4], true, true, shake, sc);
				break;
			case 6:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[5], true, true, shake, sc);
				break;
			case 7:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[6], true, true, shake, sc);
				break;
			default:
				break;
			}
		}
	}
}
