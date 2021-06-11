#pragma once
#include "Bomb.h"
#include"Load.h"

class BombMana:public MapColl
{
public:
	BombMana();
	~BombMana();

	void Init();
	void Loading(Load* load);
	void Update(bool& shakeflg, Controller* con, ExplosionMana* ex);
	void BombSpawn(const Vector2& set_pos, const Vector2& set_vec, const bool& playerSp);
	void Coll(Collision* coll, ALLVECTOR& all, Vector2 size, bool& shakeflg, Controller* con, ExplosionMana* ex);
	void MapCollUpdate(int(*collMap)[MAPX]);
	void Draw(const Vector2& sc, const Vector2& shake);
	std::vector<Bomb> bomb;

private:



	int bombTex[8];
	int bombSound;

};

