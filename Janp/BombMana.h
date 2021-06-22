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
	void Update(bool& shakeflg, Controller* con, ExplosionMana* ex);
	void BombSpawn(const Vector2& set_pos, const Vector2& set_vec, const bool& playerSp, const int& damage);
	void Coll(bool& shakeflg, Controller* con, ExplosionMana* ex);
	void MapCollUpdate(std::vector<std::vector<int>>& collMap);
	int NowBombNum();
	void Draw(const Vector2& sc, const Vector2& shake);
	std::vector<Bomb> bomb;

	int* GetBombTex() { return bombTex; }
	int GetBombSound() { return bombSound; }
private:



	int bombTex[BOMBTEX];
	int bombSound;

};

