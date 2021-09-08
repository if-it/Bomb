#pragma once
#include "MapColl.h"
#include"Collision.h"
#include"Explosion.h"
#include"RockEffectMana.h"
#define SIDE_EX_DAMAGE 4

class Enemy :
	public MapColl
{
public:
	Enemy();
	~Enemy();
	void AllInit(const int& stage, const int& mapX, const int& mapY);
	void Damage(int damage);
	bool Die(RockEffectMana*rockEffe, const int num);
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

	//���j�̖��G
	Count ex_Invincible;

	//�_���[�W���o
	Count damage_Blinking;
	bool blinking;


	int hp;
	Vector2 fVec;

};

