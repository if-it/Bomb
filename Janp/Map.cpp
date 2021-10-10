#include "Map.h"
#include<fstream>
#include<sstream>


Map::Map()
{
}


Map::~Map()
{
}

void Map::Save_Date_Load(const int& data_Num, const int& stage, Load* load)
{
	using namespace std;
	save_Data_Ori.clear();
	//ロード
	FILE* fp;
	std::string fileNama;

	fileNama = "Load/Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Map/Map_Data_F.dat";
	if (fopen_s(&fp, fileNama.c_str(), "rb") == 0)
	{
		fread_s(&save_Data_Size, sizeof(save_Data_Size), sizeof(save_Data_Size), 1, fp);
		fclose(fp);
	}
	else
	{
		save_Data_Size = 0;
	}

	FILE* fp2;
	fileNama = "Load/Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Map/Map_Data.dat";
	if (save_Data_Size > 0)
	{
		Save_Data* data_array;

		data_array = new Save_Data[save_Data_Size];
		if (fopen_s(&fp2, fileNama.c_str(), "rb") == 0)
		{
			int a = 0;
			int b = sizeof(Save_Data) * save_Data_Size;
			int c = sizeof(data_array);
			int d = sizeof(Save_Data);
			a = fread_s(data_array, sizeof(Save_Data) * save_Data_Size, sizeof(Save_Data), save_Data_Size, fp2);

			fclose(fp2);

			for (int i = 0; i < a; ++i)
			{
				save_Data_Ori.push_back(data_array[i]);
			}
		}
		else
		{
			Save_Data_Init();
		}
		delete[] data_array;
	}
	Init(stage, load);
}

void Map::Init(const int& stage, Load* load)
{
	front_Draw = false;
	StageSet(stage, load);
	stage_S = stage;
	pal = 255;
	pal_Flg = 0;
}

void Map::Save_Data_Init()
{
	save_Data_Size = 0;
	save_Data_Ori.clear();
}

void Map::Save(const int& data_Num)
{
	using namespace std;
	save_Data_Size = save_Data_Ori.size();

	std::string fileNama;

	//セーブ
	fileNama = "Load/Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Map/Map_Data_F.dat";
	FILE* fp;
	if (fopen_s(&fp, fileNama.c_str(), "wb") == 0)
	{
		fwrite(&save_Data_Size, sizeof(save_Data_Size), 1, fp);
		fclose(fp);
	}
	else
	{
		MessageBox(NULL, "Map", "SaveDataのエラー", MB_OK);
		return;
	}


	fileNama = "Load/Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Map/Map_Data.dat";
	FILE* fp2;

	if (save_Data_Size > 0)
	{

		Save_Data* data_array;

		data_array = new Save_Data[save_Data_Size];

		for (int i = 0; i < save_Data_Size; ++i)
		{
			Save_Data a = save_Data_Ori[i];
			data_array[i] = save_Data_Ori[i];
		}
		if (fopen_s(&fp2, fileNama.c_str(), "wb") == 0)
		{
			
			int a = 0;
			a = fwrite(data_array, sizeof(Save_Data), save_Data_Size, fp2);
			fclose(fp2);
		}
		else
		{
			MessageBox(NULL, "Map", "SaveDataのエラー", MB_OK);
			return;
		}

		delete[] data_array;
	}
}

void Map::StageSet(const int& stage, Load* load)
{
	using namespace std;

	map.clear();
	fleMap.clear();
	bBlockCount.clear();
	ifstream ifs;
	string fileNama;

	//マップチップデータ

	fileNama = "Load/Data/Map/Map/BombMap - Stage";
	fileNama += to_string(stage);
	fileNama += ".csv";


	int map_type = (int)(stage / 100) - (int)(stage_S / 100);
	if (map_type < 0)
	{
		map_type *= -1;
	}
	if (map_type >= 1 && stage != 0)
	{
		for (int i = 0; i < MAP_TEX_NUM; ++i)
		{
			DeleteGraph(tex[i]);
		}
		map_type = stage;
		if (map_type >= 100 && map_type < 200)load->LoadAnimeTex("Load/Texture/Map/Map/Map.png", MAP_TEX_NUM, MAP_TEX_NUM, 1, SIZE + 1, SIZE, tex);
		else if (map_type >= 200 && map_type < 300)load->LoadAnimeTex("Load/Texture/Map/Map/Map2.png", MAP_TEX_NUM, MAP_TEX_NUM, 1, SIZE + 1, SIZE, tex);
		else if (map_type >= 300 && map_type < 400)load->LoadAnimeTex("Load/Texture/Map/Map/Map3.png", MAP_TEX_NUM, MAP_TEX_NUM, 1, SIZE + 1, SIZE, tex);
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
			if (map[y][x] == 3 || map[y][x] >= 200 && map[y][x] <= 209)
			{

				for (int i = 0; i < (int)save_Data_Ori.size(); ++i)
				{
					if (save_Data_Ori[i].stage == stage && save_Data_Ori[i].map_num_X == x && save_Data_Ori[i].map_num_Y == y)
					{
						if (save_Data_Ori[i].map_num >= 205 && save_Data_Ori[i].map_num <= 209)
						{
							map[y][x] = 0;
						}
						else
						{
							map[y][x] = save_Data_Ori[i].map_num;
						}
					}
				}
			}

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
						if (map_over[n] && map_over[3 + j] &&
							map[map_num[n]][map_num[3 + j]] != 0 &&
							map[map_num[n]][map_num[3 + j]] != 3 &&
							map[map_num[n]][map_num[3 + j]] != 78 &&
							map[map_num[n]][map_num[3 + j]] != 85 &&
							!(map[map_num[n]][map_num[3 + j]] >= 24 && map[map_num[n]][map_num[3 + j]] <= 29) &&
							!(map[map_num[n]][map_num[3 + j]] >= 35 && map[map_num[n]][map_num[3 + j]] <= 39) &&
							!(map[map_num[n]][map_num[3 + j]] >= 73 && map[map_num[n]][map_num[3 + j]] <= 77) &&
							!(map[map_num[n]][map_num[3 + j]] >= 4 && map[map_num[n]][map_num[3 + j]] <= 7) &&
							!(map[map_num[n]][map_num[3 + j]] >= 80 && map[map_num[n]][map_num[3 + j]] <= 85) &&
							!(map[map_num[n]][map_num[3 + j]] >= 90 && map[map_num[n]][map_num[3 + j]] <= 94) &&
							map[map_num[n]][map_num[3 + j]] < 100)
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

			if (map[y][x] >= 200 && map[y][x] <= 204)
			{
				front_Draw = true;
			}
		}
	}
	FleMapInput();
}

void Map::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/Map/Map3.png", MAP_TEX_NUM, MAP_TEX_NUM, 1, SIZE + 1, SIZE, tex);

	load->LoadAnimeTex("Load/Texture/Map/Map/BBlock.png", 10, 10, 1, SIZE * 2, SIZE * 2, Btex);
	load->LoadAnimeTex("Load/Texture/Map/Map/toge.png", 4, 4, 1, SIZE + 1, SIZE, togeTex);
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
	while (true)
	{
		bool end_set = false;

		for (int y = 0; y < (int)map.size(); ++y)

		{
			for (int x = 0; x < (int)map[y].size(); ++x)
			{
				if (fleMap[y][x] != map[y][x])
				{
					if (map[y][x] >= 40 && map[y][x] <= 49)continue;
					if (fleMap[y][x] >= 200 && fleMap[y][x] <= 204)
					{
						int around_map_num_Y[3] = { y - 1,y,y + 1 };
						int around_map_num_X[3] = { x - 1,x,x + 1 };

						for (int i = 0; i < 3; ++i)
						{
							for (int n = 0; n < 3; ++n)
							{
								if (i == 1 && n == 1)continue;
								if (around_map_num_Y[i] >= 0 && around_map_num_Y[i] < (int)map.size() &&
									around_map_num_X[n] >= 0 && around_map_num_X[n] < (int)map[y].size() &&
									map[around_map_num_Y[i]][around_map_num_X[n]] >= 200 && map[around_map_num_Y[i]][around_map_num_X[n]] <= 204)
								{
									map[around_map_num_Y[i]][around_map_num_X[n]] += 5;
									end_set = true;
								}
							}
						}

					}
					else
					{
						bool map_save = false;
						for (int i = 0; i < (int)save_Data_Ori.size(); ++i)
						{
							if (save_Data_Ori[i].stage == stage_S && save_Data_Ori[i].map_num_X == x && save_Data_Ori[i].map_num_Y == y)
							{
								map_save = true;
								save_Data_Ori[i].map_num = map[y][x];
								break;
							}
						}
						if (!map_save)
						{
							Save_Data Init_SaveData = { stage_S,x,y,map[y][x] };
							save_Data_Ori.push_back(Init_SaveData);
						}
					}
				}
			}
		}
		if (!end_set)break;
	}
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
			case 205:
			case 206:
			case 207:
			case 208:
			case 209:
				if (pal_Flg == 0)pal_Flg = 1;
				else if (pal_Flg == 2)map[y][x] = 0;
				break;
			default:
				break;
			}
		}
	}
	if (pal_Flg == 2)
	{
		pal_Flg = 0;
		pal = 255;
	}
	else if (pal_Flg == 1)
	{
		pal -= 12;
		if (pal <= 0)
		{
			pal_Flg = 2;
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
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[0], true, false, true, shake, sc);
			}
			switch (map[y][x])
			{
			case 2:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[2], true, false, true, shake, sc);
				break;
			case 3:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[3], true, false, true, shake, sc);

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
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[1], true, false, true, shake, sc);
				break;
			case 51:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[4], true, false, true, shake, sc);
				break;
			case 52:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[5], true, false, true, shake, sc);
				break;
			case 53:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[6], true, false, true, shake, sc);
				break;
			case 58:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[7], true, false, true, shake, sc);
				break;
			case 59:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[8], true, false, true, shake, sc);
				break;
			case 60:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[9], true, false, true, shake, sc);
				break;
			case 61:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[10], true, false, true, shake, sc);
				break;
			case 62:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[11], true, false, true, shake, sc);
				break;
			case 63:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[12], true, false, true, shake, sc);
				break;
			case 64:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[13], true, false, true, shake, sc);
				break;
			case 65:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[14], true, false, true, shake, sc);
				break;
			case 66:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[15], true, false, true, shake, sc);
				break;
			case 67:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[16], true, false, true, shake, sc);
				break;
			case 68:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[17], true, false, true, shake, sc);
				break;
			case 69:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[18], true, false, true, shake, sc);
				break;
			case 70:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[19], true, false, true, shake, sc);
				break;
			case 71:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[20], true, false, true, shake, sc);
				break;
			case 72:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[21], true, false, true, shake, sc);
				break;
			case 74:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, togeTex[0], true, false, true, shake, sc);
				break;
			case 75:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, togeTex[1], true, false, true, shake, sc);
				break;
			case 76:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, togeTex[2], true, false, true, shake, sc);
				break;
			case 77:
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, togeTex[3], true, false, true, shake, sc);
				break;
			case 205:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[1], true, false, true, shake, sc);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case 206:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[4], true, false, true, shake, sc);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case 207:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[5], true, false, true, shake, sc);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case 208:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[6], true, false, true, shake, sc);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case 209:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[0], true, false, true, shake, sc);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			default:
				break;
			}

		}
	}

}

void Map::FrontDraw(const Vector2& sc, const Vector2& shake)
{
	if (front_Draw)
	{
		for (int y = 0; y < (int)map.size(); ++y)
		{
			for (int x = 0; x < (int)map[y].size(); ++x)
			{
				switch (map[y][x])
				{
				case 205:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				case 200:
					DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[1], true, false, true, shake, sc);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case 206:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				case 201:
					DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[4], true, false, true, shake, sc);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case 207:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				case 202:
					DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[5], true, false, true, shake, sc);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case 208:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				case 203:
					DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[6], true, false, true, shake, sc);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				case 209:
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
				case 204:
					DrawRotaTex(Vector2((float)(SIZE * x + SIZE / 2), (float)(SIZE * y + SIZE / 2)), Vector2(SIZE / 2, SIZE / 2), Vector2(1.0f, 1.0f), 0.0f, tex[0], true, false, true, shake, sc);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					break;
				default:
					break;
				}
			}
		}
	}
}


