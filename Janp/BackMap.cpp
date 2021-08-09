#include "BackMap.h"
#include<fstream>
#include<sstream>


BackMap::BackMap()
{
}

BackMap::~BackMap()
{
}

void BackMap::Init(const int& stage)
{

	using namespace std;

	backMap.clear();

	ifstream ifs;
	string fileNama;


	switch (stage)
	{
	case 0:
		fileNama = "Load/Data/Map/BackMap/Bomb_BackMap - demo.csv";
		break;
	case 1:
		fileNama = "Load/Data/Map/BackMap/Bomb_BackMap - Stage01.csv";
		break;
	default:
		fileNama = "Load/Data/Map/BackMap/Bomb_BackMap - demo.csv";
		break;
	}

	ifs.open(fileNama.c_str());
	if (!ifs)
	{
		MessageBox(NULL, "BackMap", "MapData�̃G���[", MB_OK);

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

void BackMap::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/BackMap.png", BACKMAP_TEX_NUM, BACKMAP_TEX_NUM, 1, SIZE, SIZE, tex);
	load->LoadAnimeTex("Load/Texture/Map/BackMap2.png", BACKMAP_TEX_NUM2, BACKMAP_TEX_NUM2, 1, SIZE*2, SIZE*2, tex2);
}

void BackMap::Update()
{
}

void BackMap::Draw(const Vector2& sc, const Vector2& shake)
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
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex2[0], true, true, shake, sc);
				break;
			case 5:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex2[1], true, true, shake, sc);
				break;
			case 6:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex2[2], true, true, shake, sc);
				break;
			case 7:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[3], true, true, shake, sc);
				break;
			case 8:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[4], true, true, shake, sc);
				break;
			case 9:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[5], true, true, shake, sc);
				break;
			case 10:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[6], true, true, shake, sc);
				break;
			case 11:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[7], true, true, shake, sc);
				break;
			case 12:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[8], true, true, shake, sc);
				break;
			case 13:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[9], true, true, shake, sc);
				break;
			default:
				break;
			}
		}
	}
}
