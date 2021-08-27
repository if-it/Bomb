#include "SideExplosionMana.h"

SideExplosionMana::SideExplosionMana()
{
}

SideExplosionMana::~SideExplosionMana()
{
}

void SideExplosionMana::Init()
{
	sideEx.clear();
	ani = Animation();
	spawn = false;
	end = Count();
}

void SideExplosionMana::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Ex/SideExTex.png", 16, 16, 1, SIZE, SIZE, tex);
}

void SideExplosionMana::Update(const bool& explosion_on, const Vector2& set_pos, std::vector<std::vector<int>>& collMap, bool& shakeflg)
{
	if (explosion_on)
	{
		if (!spawn)
		{
			shakeflg = true;
			end.flg = true;
			spawn = true;
			int xnum = 0;
			while (true)
			{
				++xnum;
				int mapPoint = MapPointer(Vector2(set_pos.x + (SIZE * xnum), set_pos.y), 1, 1, collMap);
				SideExplosion InitEx;
				InitEx.Init(Vector2(set_pos.x + (SIZE * xnum), set_pos.y), "RSideEx");
				InitEx.game_object.color = GetColor(255, 0, 0);
				InitEx.game_object.game.lr = false;
				if (WALL)
				{
					xnum = 0;
					break;
				}
				sideEx.push_back(InitEx);
			};
			while (true)
			{
				++xnum;
				int mapPoint = MapPointer(Vector2(set_pos.x - (SIZE * xnum), set_pos.y), 1, 1, collMap);
				SideExplosion InitEx;
				InitEx.Init(Vector2(set_pos.x - (SIZE * xnum), set_pos.y), "LSideEx");
				InitEx.game_object.color = GetColor(0, 0, 255);
				InitEx.game_object.game.lr = true;
				if (WALL)
				{
					xnum = 0;
					break;
				}
				sideEx.push_back(InitEx);
			};
		}


	}
	if (spawn)
	{
		for (int i = 0; i < (int)sideEx.size(); ++i)
		{
			sideEx[i].Update();
		}
		if (end.count>=80)
		{
			bool ani_End = false;
			for (int i = 0; i < (int)sideEx.size(); ++i)
			{
				if (sideEx[i].SizeSub())
				{
					ani_End = true;
				}
			}
			if(ani_End)Init();
		}
		end.Conuter(1000);
		ani.AnimationOn(1, 16);
	}
}

void SideExplosionMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)sideEx.size(); ++i)
	{
		sideEx[i].Draw(sc, shake, tex[ani.num]);
	}
}
