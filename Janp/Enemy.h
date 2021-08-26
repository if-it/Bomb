#pragma once
#include "MapColl.h"
#include"Collision.h"
#include"Explosion.h"

class Enemy :
	public MapColl
{
public:
	Enemy();
	~Enemy();
	void AllInit(const int& stage, const int& mapX, const int& mapY);
	void Damage(int damage);
	bool Die();
	struct Die_Data
	{
		int die_stage;
		int map_x;
		int map_y;
	};

	Die_Data die_Data;
protected:
	void EnemyAllUpdate(const float Enemy_Speed, const float Enemy_Max_Speed);
	bool DieChack();
	//���G
	Count invincible;
	//���j�̖��G
	Count exInvincible;
	int hp;
	Vector2 fVec;

};

