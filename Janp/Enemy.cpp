#include "Enemy.h"

Enemy::Enemy()
{
	hp = 0;
}

Enemy::~Enemy()
{
}


void Enemy::DieChack()
{
	if (hp <= 0)
	{
		game_object.dis = false;
	}
}

void Enemy::ExColl(int damage)
{
	hp -= damage;
}

