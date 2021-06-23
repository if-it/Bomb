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
	void Update(bool& shakeflg, Controller* con,ExplosionMana* ex);
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap);
	void Coll(bool& shakeflg, Controller* con);
	void Coll_End_Set(ExplosionMana* ex);
	void Draw(const Vector2& sc, const Vector2& shakeconst, const int* bombTex);


	//GameObject ex;
	ANIMATION bombAni;
	int time;
	bool playerSpawn;
	bool playerOneColl;
	bool exSpawn;
	int damage;

	//void exSpawn(const int& exSound, std::vector<Explosion>& ex);

};

