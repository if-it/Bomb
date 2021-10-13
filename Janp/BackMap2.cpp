#include "BackMap2.h"
#include<fstream>
#include<sstream>

BackMap2::BackMap2()
{
	tex = new int[MAP1];
	texArray = 0;
}

BackMap2::~BackMap2()
{
	delete[] tex;
}

void BackMap2::Init(const int& stage, Load* load)
{

	for (int i = 0; i < 5; ++i)
	{
		back_Pos[i] = Vector2(0, -726);
		back_Pos2[i] = Vector2(1280 * 2, -726);
		back_Sc[i] = Vector2();
		back_Sc2[i] = Vector2();
		back_count[i] = 0;
		back_count2[i] = 0;
	}

	int map_type = (int)(stage / 100) - (int)(stage_S / 100);
	if (map_type < 0)
	{
		map_type *= -1;
	}
	if (map_type >= 1 && stage != 0)
	{
		for (int i = 0; i < texArray; ++i)
		{
			DeleteGraph(tex[i]);
		}
		delete[] tex;
		for (int i = 0; i < 5; ++i)
		{
			DeleteGraph(stage2_Back_Tex[i]);
		}
		map_type = stage;
		if (map_type >= 100 && map_type < 200)
		{
			tex = new int[MAP1];
			texArray = MAP1;
			load->LoadAnimeTex("Load/Texture/Map/BackMap2/BackMap.png", MAP1, MAP1, 1, SIZE + 1, SIZE, tex);
		}
		else if (map_type >= 200 && map_type < 300)
		{
			tex = new int[MAP2];
			texArray = MAP2;
			load->LoadAnimeTex("Load/Texture/Map/BackMap2/BackMap2.png", MAP2, MAP2, 1, SIZE + 1, SIZE, tex);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back1.png", stage2_Back_Tex[4]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back2.png", stage2_Back_Tex[3]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back3.png", stage2_Back_Tex[2]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back4.png", stage2_Back_Tex[1]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back5.png", stage2_Back_Tex[0]);
		}
		else if (map_type >= 300 && map_type < 400)
		{
			tex = new int[MAP3];
			texArray = MAP3;
			load->LoadAnimeTex("Load/Texture/Map/BackMap2/BackMap3.png", MAP3, MAP3, 1, SIZE + 1, SIZE, tex);

			//âº
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back1.png", stage2_Back_Tex[4]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back2.png", stage2_Back_Tex[3]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back3.png", stage2_Back_Tex[2]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back4.png", stage2_Back_Tex[1]);
			load->LoadTex("Load/Texture/Map/BackObj/Stage200Back5.png", stage2_Back_Tex[0]);
		}
	}
	stage_S = stage;
	using namespace std;

	backMap.clear();

	ifstream ifs;
	string fileNama;

	fileNama = "Load/Data/Map/BackMap2/Bomb_BackMap2 - Stage";
	fileNama += to_string(stage);
	fileNama += ".csv";


	ifs.open(fileNama.c_str());
	if (!ifs)
	{
		//MessageBox(NULL, "BackMap2", "MapData2ÇÃÉGÉâÅ[", MB_OK);

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


		if (back_Sc[i].x >= 1280 * 2 * (back_count[i] + 1))
		{
			back_Pos[i].x += 1280 * 4 * (back_count[i] + 1);
			++back_count[i];
		}
		if (back_Sc[i].x <= -1280 * 2 * (back_count[i] + 1))
		{
			back_Pos[i].x += -1280 * 4 * (back_count[i] + 1);
			--back_count[i];
			if (back_count[i] <= 0)
			{
				back_count[i] = 0;
			}
		}
		if (back_Sc2[i].x >= 1280 * 4 * (back_count2[i] + 1))
		{
			back_Pos2[i].x += 1280 * 8 * (back_count2[i] + 1);
			++back_count2[i];
		}
		if (back_Sc2[i].x <= -1280 * 4 * (back_count2[i] + 1))
		{
			back_Pos2[i].x += -1280 * 8 * (back_count2[i] + 1);
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
			int texNum = backMap[y][x] - 1;
			if (texNum < 0)continue;
			DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[texNum], true, false, true, shake, sc);
		}
	}
}
