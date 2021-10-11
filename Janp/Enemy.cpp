#include "Enemy.h"

Enemy::Enemy()
{
	hp = 0;
	fVec = Vector2();
	ex_Invincible = Count();
	damage_Blinking = Count();
	blinking = false;
}

Enemy::~Enemy()
{
}

void Enemy::AllInit(const int& stage, const int& mapX, const int& mapY)
{
	die_Data.die_stage = stage;
	die_Data.map_x = mapX;
	die_Data.map_y = mapY;
}

void Enemy::EnemyAllUpdate(const float Enemy_Speed, const float Enemy_Max_Speed)
{
	const int INVEICIBLE_TIME = 60;
	const int EX_INVEICIBLE_TIME = 30;
	if (ex_Invincible.Conuter(EX_INVEICIBLE_TIME))
	{
		blinking = false;
		damage_Blinking = Count();
	}
	if (damage_Blinking.Conuter(7))
	{
		damage_Blinking.flg = true;
		if (blinking)blinking = false;
		else blinking = true;
	}
	if (ex_Invincible.flg)
	{
		damage_Blinking.flg = true;
	}
	if (fVec != Vector2())
	{
		game_object.game.allVec.vec = Vector2();
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

bool Enemy::Die(RockEffectMana* rockEffe, const int num, HpDropItemMana* hpItemMana)
{
	if (DieChack() && game_object.game.dis)
	{
		game_object.game.dis = false;
		rockEffe->Spawn(game_object.GetPos(),num);
		hpItemMana->Spawn(game_object.GetPos());
		return true;
	}
	return false;
}

