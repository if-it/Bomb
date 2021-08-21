#include "MapBombMana.h"

MapBombMana::MapBombMana()
{
}

MapBombMana::~MapBombMana()
{
}

void MapBombMana::Init(std::vector<std::vector<int>>& map)
{
	mapBomb.clear();
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == 84)
			{
				MapBomb InitMapBomb;
				InitMapBomb.Init(Vector2(SIZE * x, SIZE * y));
				mapBomb.push_back(InitMapBomb);
			}
		}
	}
}

void MapBombMana::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Map/Map/MapBomb.png", MAPBOMBTEX, MAPBOMBTEX, 1, SIZE, SIZE, tex);
}

void MapBombMana::Update(const bool& switch_on)
{
	for (int i = 0; i < (int)mapBomb.size(); ++i)
	{
		mapBomb[i].Update(switch_on);
	}
}

void MapBombMana::Coll(bool& shakeflg, Controller* con, const bool& switch_on)
{
	for (int i = 0; i < (int)mapBomb.size(); ++i)
	{
		mapBomb[i].Coll(shakeflg, con, switch_on);
	}
}

void MapBombMana::Coll_End_Set(ExplosionMana* ex)
{
	for (int i = 0; i < (int)mapBomb.size(); ++i)
	{
		mapBomb[i].Coll_End_Set(ex);
	}
}

void MapBombMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)mapBomb.size(); ++i)
	{
		mapBomb[i].Draw(sc, shake, tex);
	}
}
