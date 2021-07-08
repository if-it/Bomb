#pragma once
#pragma once
#include"MapColl.h"
#include"ExplosionMana.h"
#include"Collision.h"
#define BSPEED 10.0f
class Bomb :public MapColl
{
public:
	Bomb();
	~Bomb();
	void Init();
	void Update(bool& shakeflg, Controller* con,ExplosionMana* ex, 
		const bool& world_Time, const bool& flame_time,  Vector2 ability_Vec,const int& abi);
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap);
	void Coll(bool& shakeflg, Controller* con, const Vector2& playerVec);
	void Coll_End_Set(ExplosionMana* ex);
	void Draw(const Vector2& sc, const Vector2& shakeconst, const int* bombTex);


	//GameObject ex;
	Vector2 ability_Pos;
	Animation bombAni;
	int time;
	bool playerSpawn;
	bool playerOneColl;
	bool exSpawn;
	bool stop_Move;
	int damage;
	int ability;
	//void exSpawn(const int& exSound, std::vector<Explosion>& ex);

};

