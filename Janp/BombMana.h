#pragma once
#include "Bomb.h"
#include"Load.h"
#include"Collision.h"

#define BOMBTEX 8

class BombMana :public MapColl
{
public:
	BombMana();
	~BombMana();

	void Init();
	void Loading(Load* load);
	void Loading(const int& bombSoundC,const int*bombTexC);
	void Update(bool& shakeflg, Controller* con, ExplosionMana* ex, const bool& world_Time,
		const bool& flame_time,  Vector2 ability_Vec, const int& abi);
	void BombSpawn(const Vector2& set_pos, const Vector2& set_vec, const bool& playerSp, const int& damage);
	void Coll(bool& shakeflg, Controller* con, const Vector2& playerVec);
	void Coll_End_Set(ExplosionMana* ex);
	void MapCollUpdate(std::vector<std::vector<int>>& collMap);
	int NowBombNum();
	int NowPlayerBombNum();
	void Draw(const Vector2& sc, const Vector2& shake);
	std::vector<Bomb> bomb;

	int* GetBombTex() { return bombTex; }
	int GetBombSound() { return bombSound; }
private:


	int bombTex[BOMBTEX];
	int bombSound;

};

