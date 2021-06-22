#include "Enemy.h"

Enemy::Enemy()
{
	hp = 0;
	fVec = Vector2();
	invincible = Count();
	exInvincible = Count();
}

Enemy::~Enemy()
{
}


void Enemy::AllUpdate()
{
	const int INVEICIBLE_TIME = 60;
	const int EX_INVEICIBLE_TIME = 30;
	invincible.Conuter(INVEICIBLE_TIME);
	exInvincible.Conuter(EX_INVEICIBLE_TIME);
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

