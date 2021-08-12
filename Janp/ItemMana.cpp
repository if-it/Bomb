#include "ItemMana.h"

ItemMana::ItemMana()
{
}

ItemMana::~ItemMana()
{
}

void ItemMana::SaveData_Load(std::vector<std::vector<int>>& map, const int& data_Num, const int& stage)
{
	save_Data_Ori.clear();

	FILE* fp;

	std::string fileNama;

	switch (data_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data_F.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data_F.dat";
		break;
	}
	if (fopen_s(&fp, fileNama.c_str(), "r") == 0)
	{
		fread_s(&save_Data_Size, sizeof(save_Data_Size), sizeof(save_Data_Size), 1, fp);
		fclose(fp);
	}
	else
	{
		save_Data_Size = 0;
	}

	FILE* fp2;

	switch (data_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data.dat";
		break;
	}

	if (save_Data_Size > 0)
	{

		Save_Data* data_array;

		data_array = new Save_Data[save_Data_Size];
		if (fopen_s(&fp2, fileNama.c_str(), "r") == 0)
		{
			fread_s(data_array, sizeof(Save_Data) * save_Data_Size, sizeof(Save_Data), save_Data_Size, fp2);
			fclose(fp2);

			for (int i = 0; i < save_Data_Size; ++i)
			{
				save_Data_Ori.push_back(data_array[i]);
			}

		}
		else
		{
			Save_Data_Init();
		}
		delete data_array;
	}
	Init(map, stage);

}

void ItemMana::Save_Data_Init()
{
	save_Data_Size = 0;
	save_Data_Ori.clear();
}

void ItemMana::Save(const int& data_Num)
{
	save_Data_Size = save_Data_Ori.size();

	std::string fileNama;
	switch (data_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data_F.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data_F.dat";
		break;
	}

	FILE* fp;
	if (fopen_s(&fp, fileNama.c_str(), "w") == 0)
	{
		fwrite(&save_Data_Size, sizeof(save_Data_Size), 1, fp);
		fclose(fp);
	}
	else
	{
		MessageBox(NULL, "Item", "SaveDataのエラー", MB_OK);
		return;
	}

	FILE* fp2;

	switch (data_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Item/Item_Data.dat";
		break;
	}

	if (save_Data_Size > 0)
	{

		Save_Data* data_array;

		data_array = new Save_Data[save_Data_Size];

		for (int i = 0; i < save_Data_Size; ++i)
		{
			data_array[i] = save_Data_Ori[i];
		}
		if (fopen_s(&fp2, fileNama.c_str(), "w") == 0)
		{
			fwrite(data_array, sizeof(Save_Data), save_Data_Size, fp2);
			fclose(fp2);
		}
		else
		{
			MessageBox(NULL, "Item", "SaveDataのエラー", MB_OK);
			return;
		}

		delete data_array;
	}
}

void ItemMana::Init(std::vector<std::vector<int>>& map, const int& stage)
{
	item.clear();
	Item InitItem;
	InitItem.Init(Vector2(), 0, 0, 0, "NoName");
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			bool same = false;
			if (map[y][x] == 80 || map[y][x] == 81)
			{
				for (int i = 0; i < save_Data_Ori.size(); ++i)
				{
					if (save_Data_Ori[i].stage == stage && save_Data_Ori[i].map_num_X == x && save_Data_Ori[i].map_num_Y == y)
					{
						same = true;
						break;
					}
				}
				if (map[y][x] == 80 && !same)
				{
					InitItem.Init(Vector2((float)(SIZE * x), (float)(SIZE * y)), stage, x, y, "Item1");
					item.push_back(InitItem);
				}
				if (map[y][x] == 81 && !same)
				{
					InitItem.Init(Vector2((float)(SIZE * x), (float)(SIZE * y)), stage, x, y, "Item2");
					item.push_back(InitItem);
				}
			}
		}
	}
	ani_Num[0] = 6;
	ani_Num[1] = 2;
	ani_Num[2] = 1;
	ani_Num[3] = 1;
	ani_Num[4] = 4;
	one_Ani = false;
}

void ItemMana::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/Map/Item.png", 5, 5, 1, SIZE, 40, tex);
}

void ItemMana::Update()
{
	if (item_Ani.num == 0 && !one_Ani)
	{
		ani_Num[0] = GetRand(200)+3;
		one_Ani = true;
	}
	else
	{
		one_Ani = false;
	}
	item_Ani.Round_Trip_Animation(ani_Num[item_Ani.num], 5);
}

void ItemMana::Coll(int& get_Item)
{
	for (int i = 0; i < (int)item.size(); ++i)
	{
		if (item[i].Coll(get_Item))
		{
			save_Data_Ori.push_back(item[i].save_Data);
			break;
		}
	}
}

void ItemMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)item.size(); ++i)
	{
		item[i].Draw(sc, shake, tex[item_Ani.num]);
	}
}
