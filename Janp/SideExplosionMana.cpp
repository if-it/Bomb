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
}

void SideExplosionMana::Loading(Load* load)
{
}

void SideExplosionMana::Update(const bool& explosion_on, const Vector2& set_pos, std::vector<std::vector<int>>& collMap, bool& shakeflg)
{
	if (explosion_on)
	{
		if (!spawn)
		{
			spawn = true;
			int xnum = 0;
			while (true)
			{
				int mapPoint = MapPointer(Vector2(set_pos.x + (SIZE * xnum), set_pos.y), 1, 1, collMap);
				SideExplosion InitEx;
				InitEx.Init(Vector2(set_pos.x + (SIZE * xnum), set_pos.y), "RSideEx");
				if (WALL)
				{
					xnum = 0;
					break;
				}
				sideEx.push_back(InitEx);
				++xnum;
			};
			while (true)
			{
				int mapPoint = MapPointer(Vector2(set_pos.x - (SIZE * xnum), set_pos.y), 1, 1, collMap);
				SideExplosion InitEx;
				InitEx.Init(Vector2(set_pos.x - (SIZE * xnum), set_pos.y), "LSideEx");
				if (WALL)
				{
					xnum = 0;
					break;
				}
				sideEx.push_back(InitEx);
				++xnum;
			};
		}


	}
	if (spawn)
	{
		shakeflg = true;
		for (int i = 0; i < (int)sideEx.size(); ++i)
		{
			sideEx[i].Update();
		}
		if (ani.OneAnimation(10, 30))
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
	}
}

void SideExplosionMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)sideEx.size(); ++i)
	{
		sideEx[i].Draw(sc, shake, tex);
	}
}
