#include "FrontMap.h"
#include<fstream>
#include<sstream>

FrontMap::FrontMap()
{
	guide_Flg = false;
}

FrontMap::~FrontMap()
{
}

void FrontMap::Init(const int& stage, Load* load)
{
	guide_ani = Animation();
	using namespace std;


	if (guide_Flg)
	{
		for (int i = 0; i < 20; ++i)
		{
			DeleteGraph(guide[i]);
		}
	}
	if (stage == 304)
	{
		guide_Flg = true;
		load->LoadAnimeTex("Load/Texture/Map/FrontMap/guide.png", 20, 20, 1, 230, 316, guide);
	}
	else if (stage == 100)
	{
		guide_Flg = true;
		load->LoadAnimeTex("Load/Texture/Map/FrontMap/guide2.png", 20, 20, 1, 112, 193, guide);
	}
	else
	{
		guide_Flg = false;
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
			DeleteGraph(through_Tex[i]);
		}
		delete[] through_Tex;
		map_type = stage;
		if (map_type >= 100 && map_type < 200)
		{
			through_Tex = new int[FRONT_MAP1];
			texArray = FRONT_MAP1;
			//load->LoadAnimeTex("Load/Texture/Map/BackMap2/BackMap.png", FRONT_MAP1, FRONT_MAP1, 1, SIZE + 1, SIZE, through_Tex);


		}
		else if (map_type >= 200 && map_type < 300)
		{
			through_Tex = new int[FRONT_MAP2];
			texArray = FRONT_MAP2;
			//load->LoadAnimeTex("Load/Texture/Map/BackMap2/BackMap2.png", FRONT_MAP2, FRONT_MAP2, 1, SIZE + 1, SIZE, through_Tex);
		}
		else if (map_type >= 300 && map_type < 400)
		{
			through_Tex = new int[FRONT_MAP3];
			texArray = FRONT_MAP3;
			//load->LoadAnimeTex("Load/Texture/Map/BackMap2/BackMap3.png", FRONT_MAP3, FRONT_MAP3, 1, SIZE + 1, SIZE, through_Tex);
		}
	}

	frontMap.clear();

	ifstream ifs;
	string fileNama;

	fileNama = "Data/Map/FrontMap/Bomb_FrontMap - Stage";
	fileNama += to_string(stage);
	fileNama += ".csv";

	ifs.open(fileNama.c_str());
	if (!ifs)
	{
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
		frontMap.push_back(std::vector<int>());
		int i = 0;
		while (getline(ss, key, ','))
		{
			ss >> lineN;
			frontMap[mapNum].push_back(lineN);
		}
		++mapNum;
	}

	ifs.close();

	
	stage_S = stage;
}

void FrontMap::Loading(Load* load)
{
	//ŒÄ‚ñ‚Å‚È‚¢
}

void FrontMap::Update()
{
	if (guide_Flg)
	{
		guide_ani.AnimationOn(1, 20);
	}
}

void FrontMap::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int y = 0; y < (int)frontMap.size(); ++y)
	{
		for (int x = 0; x < (int)frontMap[y].size(); ++x)
		{
			if (frontMap[y][x] == 0)continue;
			switch (frontMap[y][x])
			{
			case 1:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, through_Tex[0], true, false, true, shake, sc);
				break;
			case 100:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, guide[guide_ani.num], true, false, true, shake, sc);
				break;
			default:
				break;
			}
		}
	}
}
