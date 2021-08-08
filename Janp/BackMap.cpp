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
		MessageBox(NULL, "BackMap", "MapDataÇÃÉGÉâÅ[", MB_OK);

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
			if (backMap[y][x] == 0)continue;
			DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[backMap[y][x] - 1], true, true, shake, sc);
		}
	}
}
