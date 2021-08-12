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
		fileNama = "Load/Data/Map/BackMap2/Bomb_BackMap2 - Stage100.csv";
		break;
	default:
		fileNama = "Load/Data/Map/BackMap2/Bomb_BackMap - demo.csv";
		break;
	}

	ifs.open(fileNama.c_str());
	if (!ifs)
	{
		MessageBox(NULL, "BackMap", "MapData2ÇÃÉGÉâÅ[", MB_OK);

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
}

void BackMap2::Update()
{
}

void BackMap2::Draw(const Vector2& sc, const Vector2& shake)
{
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
