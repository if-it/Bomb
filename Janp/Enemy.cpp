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


void Enemy::AllUpdate(const float Enemy_Speed, const float Enemy_Max_Speed)
{
	const int INVEICIBLE_TIME = 60;
	const int EX_INVEICIBLE_TIME = 30;
	invincible.Conuter(INVEICIBLE_TIME);
	exInvincible.Conuter(EX_INVEICIBLE_TIME);
	if (fVec != Vector2())
	{
		game_object.game.allVec.vec = Vector2();
	}
	if (DieChack())
	{
		game_object.game.dis = false;
	}
	game_object.game.allVec.vec.y += 0.2f;
	if (game_object.game.allVec.vec.x > 0)
	{
		game_object.game.allVec.vec.x -= Enemy_Speed;
	}
	else if (game_object.game.allVec.vec.x < 0)
	{
		game_object.game.allVec.vec.x += Enemy_Speed;
	}
	if ((game_object.game.allVec.vec.x < 0 && game_object.game.allVec.vec.x>-Enemy_Speed) ||
		(game_object.game.allVec.vec.x > 0 && game_object.game.allVec.vec.x < Enemy_Speed))
	{
		game_object.game.allVec.vec.x = 0;
	}

	if (game_object.game.allVec.vec.x > Enemy_Max_Speed)
	{
		game_object.game.allVec.vec.x = Enemy_Max_Speed;
	}
	if (game_object.game.allVec.vec.x < -Enemy_Max_Speed)
	{
		game_object.game.allVec.vec.x = -Enemy_Max_Speed;
	}

	if (fVec.y < 0)
	{
		fVec.y += 2.0f;
	}
	if (fVec.y >= 0)
	{
		fVec.y = 0;
	}
	if (fVec.x > 0)
	{
		fVec.x -= Enemy_Speed;
	}
	else if (fVec.x < 0)
	{
		fVec.x += Enemy_Speed;
	}
	if ((fVec.x < 0 && fVec.x>-Enemy_Speed) || (fVec.x > 0 && fVec.x < Enemy_Speed))
	{
		fVec.x = 0;
	}
	
	game_object.game.allVec.vec += fVec;
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

