#include "Enemy3Mana.h"

Enemy3Mana::Enemy3Mana()
{
}

Enemy3Mana::~Enemy3Mana()
{
}

void Enemy3Mana::Init(std::vector<std::vector<int>>& collMap)
{
	enemy3.clear();
	for (int y = 0; y < (int)collMap.size(); ++y)
	{
		for (int x = 0; x < (int)collMap[y].size(); ++x)
		{
			if (collMap[y][x] == 102)
			{
				Enemy3 InitEnemy3;
				InitEnemy3.Init(Vector2((float)SIZE*x,(float)SIZE*y));
				InitEnemy3.game_object.game.num = enemy3.size();
				enemy3.push_back(InitEnemy3);
			}
		}
	}
}

void Enemy3Mana::Loading(Load* load)
{
}

void Enemy3Mana::Update()
{
	for (int i = 0; i < (int)enemy3.size(); ++i)
	{
		enemy3[i].Update();
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

int Enemy3Mana::NowNum()
{
	int nowNum = 0;
	for (int i = 0; i < (int)enemy3.size(); ++i)
	{
		if (enemy3[i].game_object.game.dis)
		{
			++nowNum;
		}
	}
	return nowNum;
}

void Enemy3Mana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)enemy3.size(); ++i)
	{
		enemy3[i].Draw(sc,shake);
	}
}
