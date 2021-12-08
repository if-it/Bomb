#include "MapSwitch.h"

MapSwitch::MapSwitch()
{
}

MapSwitch::~MapSwitch()
{
}

void MapSwitch::Init(std::vector<std::vector<int>>& map)
{
	one_Coll = Count();
	ani = 0;
	mapSwitch.clear();

	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == 85)
			{
				GameObject InitSwitch = GameObject("Switch");
				InitSwitch.SetPos(Vector2(SIZE * x, SIZE * y));

				mapSwitch.push_back(InitSwitch);

			}
		}
	}
}

void MapSwitch::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/Map/MapSwitch.png", 2, 2, 1, SIZE, SIZE, tex);

}

void MapSwitch::Update()
{
	one_Coll.Conuter(40);
}

void MapSwitch::Coll(bool& switch_on)
{
	for (int i = 0; i < (int)mapSwitch.size(); ++i)
	{
		for (int n = 0; n < (int)mapSwitch[i].coll_Obj_List.size(); ++n)
		{
			std::string nameTag = mapSwitch[i].coll_Obj_List[n]->nameTag;
			if ((nameTag == "ex"||nameTag=="ex_player") && !one_Coll.flg)
			{
				one_Coll.flg = true;
				if (switch_on) 
				{
					switch_on = false;
					ani = 0;
				}
				else
				{
					switch_on = true;
					ani = 1;
				}
			}
		}
	}

}

void MapSwitch::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)mapSwitch.size(); ++i)
	{
		DrawTex(mapSwitch[i], tex[ani], true, shake, sc);
	}
}
