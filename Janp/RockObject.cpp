#include "RockObject.h"

RockObject::RockObject()
{
}

RockObject::~RockObject()
{
}

void RockObject::Init(std::vector<std::vector<int>>& map)
{
	game_object = GameObject("RockObj",false,Vector2(64.0f,64.0f));
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == 99)
			{
				game_object.SetPos(Vector2(SIZE * x, SIZE * y));
				game_object.game.dis = true;
				break;
			}
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		rockLihgtEffect[i].Init(Vector2());
	}
	light_Ani = Animation();
	count = 90;
}

void RockObject::Loading(int* tex)
{
	light_Tex = tex;
}

void RockObject::Update()
{
	if (game_object.game.dis)
	{
		light_Ani.Round_Trip_Animation(1, 5);
		++count;
		if (count >= 70)
		{
			count = 0;
			for (int i = 0; i < 5; ++i)
			{
				if (!rockLihgtEffect[i].game_object.game.dis)
				{
					rockLihgtEffect[i].Init(Vector2(game_object.GetPos().x + 32, game_object.GetPos().y - SIZE * 21));
					rockLihgtEffect[i].game_object.game.dis = true;
					break;
				}
			}
		}
		for (int i = 0; i < 5; ++i)
		{
			rockLihgtEffect[i].Update();
		}
	}
}

void RockObject::Draw(const Vector2& sc, const Vector2& shake)
{
	DrawTex(game_object, light_Tex[light_Ani.num], true, shake, sc);
	for (int i = 0; i < 5; ++i)
	{
		rockLihgtEffect[i].Draw(sc, shake);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
