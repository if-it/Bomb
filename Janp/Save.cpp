#include "Save.h"

Save::Save()
{
	game_object = GameObject("Save",true,Vector2(128.0f, 128.0f));
	game_object.color = COLOR(0, 120, 0);
}

Save::~Save()
{
}

void Save::Init(std::vector<std::vector<int>>& map)
{
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == 73)
			{
				game_object.SetPos(Vector2((float)(SIZE * x), (float)(SIZE * y)));
				map[y][x] = 0;
				break;
			}
		}
	}
}

void Save::Loading(Load* load)
{
}

void Save::Update()
{
}

void Save::Draw(const Vector2& sc, const Vector2& shake)
{
	Box(game_object, true,shake,sc);
}
