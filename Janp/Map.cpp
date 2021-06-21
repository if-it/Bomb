#include "Map.h"
#include<fstream>
#include<sstream>

Map::Map()
{
}


Map::~Map()
{
}

void Map::Init(int stage)
{
	StageSet(stage);
}

void Map::StageSet(int stage)
{
	using namespace std;

	map.clear();
	fleMap.clear();
	bBlockCount.clear();
	ifstream ifs;
	string fileNama;

	switch (stage)
	{
	case 0:
		fileNama = "Load/Data/Map/DemoMap.dat";
		break;
	default:
		fileNama = "Load/Data/Map/DemoMap.dat";
		break;
	}

	ifs.open(fileNama.c_str());
	if (!ifs)
	{
		MessageBox(NULL, "Map", "Map‚ÌƒGƒ‰[", MB_OK);

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
		map.push_back(std::vector<int>());
		fleMap.push_back(std::vector<int>());
		bBlockCount.push_back(std::vector<int>());
		int i = 0;
		while (getline(ss, key, ','))
		{
			ss >> lineN;
			bBlockCount[mapNum].push_back(0);
			fleMap[mapNum].push_back(lineN);
			map[mapNum].push_back(lineN);
		}
		++mapNum;
	}

	ifs.close();
}

void Map::FleMapInput()
{
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			fleMap[y][x] = map[y][x];
		}
	}
}




void Map::Update()
{
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			fleMap[y][x] = map[y][x];
			switch (map[y][x])
			{
			case 41:
				bBlockCount[y][x]++;
				if (bBlockCount[y][x] == 60 * 3)
				{
					map[y][x]++;
					bBlockCount[y][x] = 0;
				}
				break;
			case 42:
			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
			case 48:
			case 49:
				bBlockCount[y][x]++;
				if (bBlockCount[y][x] == B_MAX_COUNT)
				{
					map[y][x]++;
					bBlockCount[y][x] = 0;
					if (map[y][x] == 50)
					{
						map[y][x] = 40;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}



void Map::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{

			if (map[y][x] == 1 || (map[y][x] >= 8 && map[y][x] <= 23))
			{
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[1], true, true, shake, sc);

			}
			switch (map[y][x])
			{
			case 2:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[2], true, true, shake, sc);
				break;
			case 3:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[3], true, true, shake, sc);
				break;
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
			case 48:
			case 49:
				DrawTex(Vector2((float)(SIZE * x - SIZE / 2), (float)(SIZE * y - SIZE / 2)), Btex[map[y][x] - 40], true, true, shake, sc);
				break;
			case 65:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[4], true, true, shake, sc);
				break;
			default:
				break;
			}
			/*if (map[y][x] == 2)
			{

			}
			if (map[y][x] == 3)
			{

			}
			if (map[y][x] == 48)
			{

			}
			if (map[y][x] == 60)
			{

			}
			if (map[y][x] == 61)
			{

			}
			if (map[y][x] == 62)
			{

			}
			if (map[y][x] == 63)
			{

			}
			*/
		}
	}
}