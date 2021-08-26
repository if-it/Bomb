#include "Enemy1Mana.h"

Enemy1Mana::Enemy1Mana()
{
	enemy1Tex = 0;
}

Enemy1Mana::~Enemy1Mana()
{
}

void Enemy1Mana::Init(std::vector<std::vector<int>>& collMap, const int& stage)
{
	enemy1.clear();
	for (int y = 0; y < (int)collMap.size(); ++y)
	{
		for (int x = 0; x < (int)collMap[y].size(); ++x)
		{
			if (collMap[y][x] == 100)
			{
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
					Enemy1 InitEnemy1;
					InitEnemy1.Init(Vector2((float)SIZE * x, (float)SIZE * y));
					InitEnemy1.game_object.game.num = enemy1.size();
					InitEnemy1.AllInit(stage, x, y);
					enemy1.push_back(InitEnemy1);
				}
			}
		}
	}
}

void Enemy1Mana::Save()
{
	die_List.clear();
}

void Enemy1Mana::Update()
{
	for (int i = 0; i < (int)enemy1.size(); ++i)
	{
		enemy1[i].Update();
		if (enemy1[i].Die())
		{
			die_List.push_back(enemy1[i].die_Data);
		}
		
	}
	if (NowNum() == 0)
	{
		enemy1.clear();
	}
}

void Enemy1Mana::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	for (int i = 0; i < (int)enemy1.size(); ++i)
	{
		enemy1[i].MapCollUpdate(collMap);
	}
}

void Enemy1Mana::MoveChack(const Vector2& pos, Collision* coll)
{
	for (int i = 0; i < (int)enemy1.size(); ++i)
	{
		enemy1[i].MoveChack(pos, coll);
	}
}


void Enemy1Mana::Coll(std::vector<Explosion>& ex)
{
	for (int i = 0; i < (int)enemy1.size(); ++i)
	{
		enemy1[i].Coll(ex);
	}
}

int Enemy1Mana::NowNum()
{
	int nowNum = 0;
	for (int i = 0; i < (int)enemy1.size(); ++i)
	{
		if (enemy1[i].game_object.game.dis)
		{
			++nowNum;
		}
	}
	return nowNum;
}

void Enemy1Mana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)enemy1.size(); ++i)
	{
		enemy1[i].Draw(sc, shake);
	}
}
