#include "Enemy.h"

Enemy::Enemy()
{
	hp = 0;
	fVec = Vector2();
}

Enemy::~Enemy()
{
}


bool Enemy::DieChack()
{
	if (hp <= 0)
	{
		return true;
	}
	return false;
}

void Enemy::Damage(int damage)
{
	hp -= damage;
}

