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
	void Update(bool& shakeflg, Controller* con, std::vector<Explosion>& ex);
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size, bool& shakeflg, Controller* con, std::vector<Explosion>& ex);
	void MapCollUpdate(int(*collMap)[MAPX]);
	void Draw(const Vector2& sc, const Vector2& shake);

	int bombTex[8];
	int exTex[4];
	int exSound;

	std::vector<Bomb> bomb;
};

