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

	fileNama = "Data/Map/BackMap/Bomb_BackMap - Stage";
	fileNama += to_string(stage);
	fileNama += ".csv";

	ifs.open(fileNama.c_str());
	if (!ifs)
	{
		//MessageBox(NULL, "BackMap", "MapDataÇÃÉGÉâÅ[", MB_OK);

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
	load->LoadAnimeTex("Load/Texture/Map/BackMap/BackMap.png", BACKMAP_TEX_NUM, BACKMAP_TEX_NUM, 1, SIZE, SIZE, tex);
	load->LoadAnimeTex("Load/Texture/Map/BackMap/BackMap2.png", BACKMAP_TEX_NUM2, BACKMAP_TEX_NUM2, 1, SIZE * 2 + 1, SIZE * 2, tex2);
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
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[0], true, false, true, shake, sc);
				break;
			case 2:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[1], true, false, true, shake, sc);
				break;
			case 3:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[2], true, false, true, shake, sc);
				break;
			case 4:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[0], true, false, true, shake, sc);
				break;
			case 5:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[1], true, false, true, shake, sc);
				break;
			case 6:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[2], true, false, true, shake, sc);
				break;
			case 7:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[3], true, false, true, shake, sc);
				break;
			case 8:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[4], true, false, true, shake, sc);
				break;
			case 9:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[5], true, false, true, shake, sc);
				break;
			case 10:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[6], true, false, true, shake, sc);
				break;
			case 11:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[7], true, false, true, shake, sc);
				break;
			case 12:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[8], true, false, true, shake, sc);
				break;
			case 13:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[9], true, false, true, shake, sc);
				break;
			case 14:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[10], true, false, true, shake, sc);
				break;
			case 15:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[11], true, false, true, shake, sc);
				break;
			case 16:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)),
					Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[12], true, false, true, shake, sc);
				break;
			case 17:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[6], true, false, true, shake, sc);
				break;
			case 18:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[7], true, false, true, shake, sc);
				break;
			case 19:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[3], true, false, true, shake, sc);
				break;
			case 20:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[4], true, false, true, shake, sc);
				break;
			case 21:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[5], true, false, true, shake, sc);
				break;
			case 22:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[8], true, false, true, shake, sc);
				break;
			case 23:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[9], true, false, true, shake, sc);
				break;
			case 24:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[10], true, false, true, shake, sc);
				break;
			case 25:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE), (float)(SIZE * y + SIZE)),
					Vector2(SIZE, SIZE), Vector2(1.0f, 1.0f), 0.0f, tex2[11], true, false, true, shake, sc);
				break;
			default:
				break;
			}
		}
	}
}
