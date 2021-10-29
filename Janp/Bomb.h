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
	void Update(bool& shakeflg, Controller* con,ExplosionMana* ex, const bool& world_Time, const bool& flame_time, const Vector2& ability_Vec);
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap);
	void Coll(bool& shakeflg, Controller* con);
	void Coll_End_Set(ExplosionMana* ex);
	void Map_Coll(std::vector<std::vector<int>>& collMap);
	void Draw(const Vector2& sc, const Vector2& shake, const int* bombTex);

	void MapJub(const int& mapPoint, const int& pointNum);
	Animation bombAni;
	int time;
	bool playerSpawn;
	bool playerOneColl;
	bool exSpawn;
	bool stopMove;
	int damage;


};

