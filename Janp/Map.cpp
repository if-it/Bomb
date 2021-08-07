#include "Map.h"
#include<fstream>
#include<sstream>

Map::Map()
{
}


Map::~Map()
{
}

void Map::Save_Date_Load(const int& date_Num, const int& stage)
{
	Init(stage);

	FILE* fp;

	std::string fileNama;
	switch (date_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Map/Map_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Map/Map_Data.dat";
		break;
	}
	if (fopen_s(&fp, fileNama.c_str(), "r") == 0)
	{
		fread_s(&save_Data, sizeof(save_Data), sizeof(save_Data), 1, fp);

		Init(stage);


		fclose(fp);
	}
	else
	{
		save_Data = { 1,1 };

		Init(stage);
	}

}

void Map::Init(const int& stage)
{
	StageSet(stage);
}

void Map::Save_Data_Init(const int& stage)
{
	Init(stage);
}

void Map::Save(const int& date_Num)
{
	save_Data = { 2,2 };
	FILE* fp;

	std::string fileNama;
	switch (date_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Map/Map_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Map/Map_Data.dat";
		break;
	}
	if (fopen_s(&fp, fileNama.c_str(), "w") == 0)
	{
		fwrite(&save_Data, sizeof(save_Data), 1, fp);
		fclose(fp);
	}
	else
	{
		MessageBox(NULL, "Map", "SaveDataのエラー", MB_OK);
		return;
	}
}

void Map::StageSet(const int& stage)
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
		fileNama = "Load/Data/Map/BombMap - demo.csv";
		break;
	case 1:
		fileNama = "Load/Data/Map/BombMap - Stage01.csv";
		break;
	default:
		fileNama = "Load/Data/Map/BombMap - demo.csv";
		break;
	}

	ifs.open(fileNama.c_str());
	if (!ifs)
	{
		MessageBox(NULL, "Map", "MapDataのエラー", MB_OK);

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

	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == 1)
			{


				int map_num[6] = { y - 1,y,y + 1,x - 1,x,x + 1 };

				bool map_check[3][3] = { {0,0,0},{0,0,0},{0,0,0} };

				bool map_over[6] = { 0,1,0,0,1,0 };

				if (map_num[0] >= 0)
				{
					map_over[0] = true;
				}
				if (map_num[2] < (int)map.size())
				{
					map_over[2] = true;
				}
				if (map_num[3] >= 0)
				{
					map_over[3] = true;
				}
				if (map_num[5] < (int)map[0].size())
				{
					map_over[5] = true;
				}

				for (int n = 0; n < 3; ++n)
				{
					for (int j = 0; j < 3; ++j)
					{
						if (map_over[n] && map_over[3 + j] && map[map_num[n]][map_num[3 + j]] != 0 &&
							map_over[n] && map_over[3 + j] && map[map_num[n]][map_num[3 + j]] != 3 &&
							!(map[map_num[n]][map_num[3 + j]] >= 73 && map[map_num[n]][map_num[3 + j]] <= 77) &&
							!(map[map_num[n]][map_num[3 + j]] >= 4 && map[map_num[n]][map_num[3 + j]] <= 7)&&
							!(map[map_num[n]][map_num[3 + j]] >= 80 && map[map_num[n]][map_num[3 + j]] <= 82))
						{
							map_check[n][j] = true;
						}
					}
				}

				int map_kado = 101010;
				for (int n = 0; n < 3; ++n)
				{
					for (int j = 0; j < 3; ++j)
					{
						if (map_check[n][j])
						{
							if (n == 1 && j == 1)
							{
								continue;
							}
							if (n == 0)
							{
								map_kado += (j + 2) * 10000;
							}
							else if (n == 1)
							{
								map_kado += (j + 2) * 100;
							}
							else
							{
								map_kado += j + 2;
							}
						}
					}
				}

				switch (map_kado)
				{
				case 101010:
				case 101012:
				case 101014:
				case 101016:
				case 121014:
				case 121016:
				case 121010:
				case 121012:
				case 141010:
				case 141012:
				case 141014:
				case 141016:
				case 161010:
				case 161012:
				case 161014:
				case 161016:
					//孤立
					map[y][x] = 72;
					break;
				case 101213:
				case 101217:
				case 101413:
				case 101415:
				case 101615:
				case 101617:
				case 101613:
				case 121213:
				case 121413:
				case 121415:
				case 131617:
				case 131410:
				case 131412:
				case 131414:
				case 131210:
				case 131212:
				case 131213:
				case 131214:
				case 131215:
				case 131216:
				case 131217:
				case 131219:
				case 131610:
				case 131612:
				case 131619:
				case 131413:
				case 131415:
				case 131614:
				case 131615:
				case 131416:
				case 131417:
				case 131613:
				case 131616:
				case 141213:
				case 141217:
				case 141413:
				case 141415:
				case 141613:
				case 151010:
				case 151213:
				case 151410:
				case 151412:
				case 151413:
				case 151415:
				case 151610:
				case 151612:
				case 151613:
				case 151615:
				case 161213:
				case 161217:
				case 161413:
				case 161415:
				case 161613:
				case 161615:
				case 161617:
				case 171210:
				case 171212:
				case 171213:
				case 171214:
				case 171215:
				case 171216:
				case 171217:
				case 171219:
				case 171413:
				case 171415:
				case 171610:
				case 171612:
				case 171613:
				case 171614:
				case 171615:
				case 171616:
				case 171617:
				case 191213:
				case 191413:
				case 191415:
				case 191613:
				case 191619:
					//埋まってる
					map[y][x] = 1;
					break;
				case 101210:
				case 101212:
				case 101214:
				case 101216:
				case 121210:
				case 121212:
				case 121214:
				case 121216:
				case 141210:
				case 141212:
				case 141214:
				case 141216:
				case 161210:
				case 161212:
				case 161214:
				case 161216:
					//1マス右
					map[y][x] = 70;
					break;
				case 101410:
				case 101412:
				case 101414:
				case 101416:
				case 121410:
				case 121412:
				case 121414:
				case 121416:
				case 141410:
				case 141412:
				case 141414:
				case 141416:
				case 161410:
				case 161412:
				case 161414:
				case 161416:
					//1マス左
					map[y][x] = 71;
					break;
				case 101619:
				case 121613:
				case 121615:
				case 121617:
				case 121619:
				case 141615:
				case 141617:
				case 141619:
				case 161619:
					//上
					map[y][x] = 50;
					break;
				case 101013:
				case 101015:
				case 101017:
				case 101019:
				case 121013:
				case 121015:
				case 121017:
				case 121019:
				case 141013:
				case 141015:
				case 141017:
				case 141019:
				case 161013:
				case 161015:
				case 161017:
				case 161019:
					//1マス縦上
					map[y][x] = 68;
					break;
				case 101610:
				case 101612:
				case 101614:
				case 101616:
				case 121610:
				case 121612:
				case 121614:
				case 121616:
				case 141610:
				case 141612:
				case 141614:
				case 141616:
				case 161610:
				case 161612:
				case 161614:
				case 161616:
					//1マス真ん中横
					map[y][x] = 67;
					break;
				case 131013:
				case 131015:
				case 131017:
				case 131019:
				case 151013:
				case 151015:
				case 171013:
				case 171015:
				case 171017:
				case 171019:
				case 191013:
				case 191015:
				case 191017:
				case 191019:
					//1マス真ん中縦
					map[y][x] = 66;
					break;
				case 131010:
				case 131012:
				case 131014:
				case 131016:
				case 151012:
				case 151014:
				case 151016:
				case 151017:
				case 151019:
				case 171010:
				case 171012:
				case 171014:
				case 171016:
				case 191010:
				case 191012:
				case 191014:
				case 191016:
					//1マス縦下
					map[y][x] = 69;
					break;
				case 101215:
				case 101219:
				case 121215:
				case 121217:
				case 121219:
				case 141215:
				case 141219:
				case 161215:
				case 161219:
					//右上角1
					map[y][x] = 58;
					break;
				case 151210:
				case 151212:
				case 151214:
				case 151216:
				case 191210:
				case 191212:
				case 191214:
				case 191216:
				case 151614:
					//右下角1
					map[y][x] = 60;
					break;
				case 101417:
				case 101419:
				case 121417:
				case 121419:
				case 131419:
				case 141417:
				case 141419:
				case 151414:
				case 151416:
				case 161417:
				case 161419:
					//左上角1
					map[y][x] = 59;
					break;

				case 151215:
				case 151217:
				case 151219:
				case 191215:
				case 191217:
				case 191219:
					//右
					map[y][x] = 52;
					break;
				case 151617:
				case 151619:
					//左上角2
					map[y][x] = 63;
					break;
				case 151417:
				case 151419:
				case 171417:
				case 171419:
				case 191417:
				case 191419:
					//左
					map[y][x] = 53;
					break;
				case 171410:
				case 171412:
				case 171414:
				case 171416:
				case 191410:
				case 191412:
				case 191414:
				case 191416:
					//左下角1
					map[y][x] = 61;
					break;
				case 151616:
				case 191610:
				case 191612:
				case 191614:
				case 191616:
					//下
					map[y][x] = 51;
					break;
				case 171619:
					//右上角2
					map[y][x] = 62;
					break;
				case 191615:
					//右下角2
					map[y][x] = 64;
					break;
				case 191617:
					//左下角2
					map[y][x] = 65;
					break;
				default:
					map[y][x] = 1;
					break;
				}
			}
		}
	}

}

void Map::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/Map.png", MAP_TEX_NUM, MAP_TEX_NUM, 1, SIZE, SIZE, tex);
	load->LoadAnimeTex("Load/Texture/Map/BBlock.png", 10, 10, 1, SIZE * 2, SIZE * 2, Btex);
	load->LoadAnimeTex("Load/Texture/Map/toge.png", 4, 4, 1, SIZE, SIZE, togeTex);
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

			if (map[y][x] == 1 || (map[y][x] >= 54 && map[y][x] <= 57))
			{
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[0], true, true, shake, sc);

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
			case 50:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[1], true, true, shake, sc);
				break;
			case 51:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[4], true, true, shake, sc);
				break;
			case 52:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[5], true, true, shake, sc);
				break;
			case 53:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[6], true, true, shake, sc);
				break;
			case 58:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[7], true, true, shake, sc);
				break;
			case 59:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[8], true, true, shake, sc);
				break;
			case 60:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[9], true, true, shake, sc);
				break;
			case 61:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[10], true, true, shake, sc);
				break;
			case 62:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[11], true, true, shake, sc);
				break;
			case 63:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[12], true, true, shake, sc);
				break;
			case 64:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[13], true, true, shake, sc);
				break;
			case 65:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[14], true, true, shake, sc);
				break;
			case 66:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[15], true, true, shake, sc);
				break;
			case 67:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[16], true, true, shake, sc);
				break;
			case 68:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[17], true, true, shake, sc);
				break;
			case 69:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[18], true, true, shake, sc);
				break;
			case 70:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[19], true, true, shake, sc);
				break;
			case 71:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[20], true, true, shake, sc);
				break;
			case 72:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), tex[21], true, true, shake, sc);
				break;
			case 74:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), togeTex[0], true, true, shake, sc);
				break;
			case 75:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), togeTex[1], true, true, shake, sc);
				break;
			case 76:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), togeTex[2], true, true, shake, sc);
				break;
			case 77:
				DrawTex(Vector2((float)(SIZE * x), (float)(SIZE * y)), togeTex[3], true, true, shake, sc);
				break;
			}

		}
	}
	
}


