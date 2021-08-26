#pragma once
#define ENEMY3TEX 6
#include "Enemy3.h"
#include"Load.h"

using Die_Data = Enemy::Die_Data;

class Enemy3Mana :
	public Draw
{
public:
	Enemy3Mana();
	~Enemy3Mana();
	void Init(std::vector<std::vector<int>>& collMap, Load* load, const int& stage);
	void Save();
	void Update();
	void MapCollUpdate(std::vector<std::vector<int>>& collMap);
	void Coll(std::vector<Explosion>& ex);
	int NowNum();
	void Draw(const Vector2& sc, const Vector2& shake);
	std::vector<Enemy3> enemy3;
private:
	int enemy3Tex[ENEMY3TEX];
	bool enemy_Spawn;
	bool one_Load_Tex;
	Animation ani;
	std::vector<Die_Data> die_List;
};

