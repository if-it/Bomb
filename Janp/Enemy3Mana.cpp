#include "Enemy3Mana.h"

Enemy3Mana::Enemy3Mana()
{
	enemy_Spawn = false;
	one_Load_Tex = false;
	die_List.clear();
}

Enemy3Mana::~Enemy3Mana()
{
}

void Enemy3Mana::Init(std::vector<std::vector<int>>& collMap, Load* load, const int& stage)
{
	ani = Animation();
	enemy3.clear();
	enemy_Spawn = false;
	for (int y = 0; y < (int)collMap.size(); ++y)
	{
		for (int x = 0; x < (int)collMap[y].size(); ++x)
		{
			if (collMap[y][x] == 102)
			{
				if (!one_Load_Tex)
				{
					one_Load_Tex = true;
					load->LoadAnimeTex("Load/Texture/Enemy/Enemy3/Enemy3.png", ENEMY3TEX, ENEMY3TEX, 1, SIZE, SIZE, enemy3Tex);
				}
				bool die_on = false;
				for (int i = 0; i < die_List.size(); ++i)
				{
					if (die_List[i].die_stage == stage && die_List[i].map_x == x && die_List[i].map_y == y)
					{
						die_on = true;
						break;
					}
				}
				if (!die_on)
				{
					Enemy3 InitEnemy3;
					InitEnemy3.Init(Vector2((float)SIZE * x, (float)SIZE * y));
					InitEnemy3.game_object.game.num = enemy3.size();
					InitEnemy3.AllInit(stage, x, y);
					enemy3.push_back(InitEnemy3);
					enemy_Spawn = true;
				}
			}
		}
	}
	if (one_Load_Tex && !enemy_Spawn)
	{
		one_Load_Tex = false;
		for (int i = 0; i < ENEMY3TEX; ++i)
		{
			DeleteGraph(enemy3Tex[i]);
		}
	}
}

void Enemy3Mana::Save()
{
	die_List.clear();
}


void Enemy3Mana::Update(RockEffectMana* rockEffe)
{
	ani.AnimationOn(10, ENEMY3TEX);
	int now_Num = 0;
	for (int i = 0; i < (int)enemy3.size(); ++i)
	{
		if (enemy3[i].game_object.game.dis)
		{

			enemy3[i].Update();
			if (enemy3[i].Die(rockEffe, GetRand(2)+3))
			{
				die_List.push_back(enemy3[i].die_Data);
			}
			++now_Num;
		}
	}
	if (now_Num == 0)
	{
		enemy3.clear();
	}
}

void Enemy3Mana::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	for (int i = 0; i < (int)enemy3.size(); ++i)
	{
		enemy3[i].MapCollUpdate(collMap);
	}
}

void Enemy3Mana::Coll(std::vector<Explosion>& ex)
{
	for (int i = 0; i < (int)enemy3.size(); ++i)
	{
		enemy3[i].Coll(ex);
	}
}

void Enemy3Mana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)enemy3.size(); ++i)
	{
		enemy3[i].Draw(sc, shake, enemy3Tex[ani.num]);
	}
}
