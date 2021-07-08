#include "Bomb.h"



Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

void Bomb::Init()
{
	game_object = GameObject("Bomb", false);
	bombAni = Animation();
	time = 0;
	playerOneColl = false;
	playerSpawn = false;
	damage = 1;
	exSpawn = false;
	stop_Move = false;
	ability_Pos = Vector2();
	ability = 0;
}

void Bomb::Update(bool& shakeflg, Controller* con, ExplosionMana* ex, const bool& world_Time,
	const bool& flame_time, Vector2 ability_Vec, const int& abi)
{
	ability = abi;
	time++;
	if (game_object.game.dis || stop_Move)
	{
		if (stop_Move && abi == 7)
		{
			game_object.SetPos(ability_Vec + ability_Pos);
			stop_Move = false;
			game_object.game.dis = true;
			/*stopMove = false;
			game_object.game.allVec.vec = ability_Vec;*/
		}
		else if (!stop_Move)
		{


			game_object.game.allVec.vec.y += 0.1f;

			if (game_object.game.allVec.vec.x > 0)
			{
				game_object.game.allVec.vec.x -= 0.1f;
			}
			else if (game_object.game.allVec.vec.x < 0)
			{
				game_object.game.allVec.vec.x += 0.1f;
			}
			if ((game_object.game.allVec.vec.x < 0 && game_object.game.allVec.vec.x>-0.1f) ||
				(game_object.game.allVec.vec.x > 0 && game_object.game.allVec.vec.x < 0.1f))
			{
				game_object.game.allVec.vec.x = 0;
			}

			if (bombAni.OneAnimation(28, 8))
			{
				game_object.game.dis = false;
				ex->ExSpawn(game_object, damage);
				shakeflg = true;
				con->Shake(1000, 200);
			}
		}
		if (time == 60)
		{
			playerOneColl = false;
		}
	}
}

void Bomb::Map_Coll_Update(std::vector<std::vector<int>>& collMap)
{
	if (game_object.game.dis)Map_Coll(collMap);
}

void Bomb::Coll(bool& shakeflg, Controller* con, const Vector2& playerVec)
{
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "Player")
		{
			if (!playerOneColl)
			{
				shakeflg = true;
				game_object.game.dis = false;
				exSpawn = true;
				con->Shake(1000, 300);
			}
		}
		if (nameTag == "Enemy1" || nameTag == "Enemy2")
		{

			shakeflg = true;
			game_object.game.dis = false;
			exSpawn = true;
			con->Shake(1000, 300);
		}
		if (nameTag == "Ability")
		{
			if (ability >= 1 && ability <= 3)
			{
				stop_Move = true;
				game_object.game.dis = false;
				ability_Pos = game_object.GetPos() - playerVec;
			}
		}
	}

}

void Bomb::Coll_End_Set(ExplosionMana* ex)
{
	if (exSpawn)
	{
		exSpawn = false;
		ex->ExSpawn(game_object, damage);
	}
}




//void Bomb::exSpawn(const int& exSound, std::vector<Explosion>& ex)
//{
//	game_object.dis = false;
//
//	static Explosion InitEx;
//	InitEx.Init();
//	InitEx.game_object.dis = true;
//	InitEx.game_object.allVec = game_object.allVec;
//	InitEx.game_object.allVec.pos -= SIZE/2;
//	ex.push_back(InitEx);
//}

void Bomb::Draw(const Vector2& sc, const Vector2& shake, const int* bombTex)
{

	DrawRotaTex(game_object, bombTex[bombAni.num], true, shake, sc);

}


