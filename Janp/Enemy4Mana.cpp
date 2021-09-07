#include "Enemy4Mana.h"

Enemy4Mana::Enemy4Mana()
{
	enemy_Spawn = false;
	one_Load_Tex = false;
}

Enemy4Mana::~Enemy4Mana()
{
}

void Enemy4Mana::Init(std::vector<std::vector<int>>& collMap, Load* load, const int& stage)
{
	enemy4.clear();
	ani = Animation();
	for (int y = 0; y < (int)collMap.size(); ++y)
	{
		for (int x = 0; x < (int)collMap[y].size(); ++x)
		{
			if (collMap[y][x] == 103)
			{
				if (!one_Load_Tex)
				{
					one_Load_Tex = true;
					load->LoadTex("Load/Texture/Enemy/Enemy4/Enemy4.png", tex);
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
					Enemy4 InitEnemy4;
					InitEnemy4.Init(Vector2(SIZE * x, SIZE * y));
					InitEnemy4.game_object.game.num = enemy4.size();
					InitEnemy4.AllInit(stage, x, y);
					enemy4.push_back(InitEnemy4);
					enemy_Spawn = true;
				}
			}
		}
	}
}

void Enemy4Mana::Save()
{
	die_List.clear();
}

void Enemy4Mana::Update()
{
	ani.AnimationOn(10, 2);
	for (int i = 0; i < (int)enemy4.size(); ++i)
	{
		enemy4[i].Update();
		if (enemy4[i].Die())
		{
			die_List.push_back(enemy4[i].die_Data);
		}
	}
	if (NowNum() == 0)
	{
		enemy4.clear();
	}
}

void Enemy4Mana::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	for (int i = 0; i < (int)enemy4.size(); ++i)
	{
		enemy4[i].MapCollUpdate(collMap);
	}
}

void Enemy4Mana::MoveChack(const Vector2& pos, Collision* coll)
{
	for (int i = 0; i < (int)enemy4.size(); ++i)
	{
		enemy4[i].MoveChack(pos, coll);
	}
}

void Enemy4Mana::Coll(std::vector<Explosion>& ex)
{
	for (int i = 0; i < (int)enemy4.size(); ++i)
	{
		enemy4[i].Coll(ex);
	}
}

int Enemy4Mana::NowNum()
{
	int nowNum = 0;
	for (int i = 0; i < (int)enemy4.size(); ++i)
	{
		if (enemy4[i].game_object.game.dis)
		{
			++nowNum;
		}
	}
	return nowNum;
}

void Enemy4Mana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)enemy4.size(); ++i)
	{
		enemy4[i].Draw(sc, shake, tex);
	}
}
