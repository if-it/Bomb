#include "SaveMana.h"

SaveMana::SaveMana()
{
}

SaveMana::~SaveMana()
{
}

void SaveMana::Init(std::vector<std::vector<int>>& map)
{
	Save InitSave;
	InitSave.Init(Vector2());
	save.clear();
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == 73)
			{
				InitSave.Init(Vector2((float)(SIZE * x), (float)(SIZE * y)));
				save.push_back(InitSave);
				map[y][x] = 0;
			}
		}
	}
}

void SaveMana::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/Map/Save.png", 2, 2, 1, 128, 64, tex);
}

void SaveMana::Update()
{
	for (int i = 0; i < (int)save.size(); ++i)
	{
		save[i].Update();
	}
}

void SaveMana::Save_Mode()
{
	for (int i = 0; i < (int)save.size(); ++i)
	{
		save[i].Save_Mode();
	}
}

void SaveMana::Coll()
{
	for (int i = 0; i < (int)save.size(); ++i)
	{
		save[i].Coll();
	}
}

void SaveMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)save.size(); ++i)
	{
		save[i].Draw(sc, shake, tex);
	}
}
