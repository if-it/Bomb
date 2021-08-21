#pragma once
#include "Draw.h"
#include"ExplosionMana.h"
class MapBomb :
	public Draw
{
public:
	MapBomb();
	~MapBomb();
	void Init(const Vector2& pos);
	void Update(const bool& switch_on);
	void Coll(bool& shakeflg, Controller* con, const bool&switch_on);
	void Coll_End_Set(ExplosionMana* ex);
	void Draw(const Vector2& sc, const Vector2& shake, int* tex);

private:
	Count bomb_count;
	Animation ani;
	bool exSpawn;
	int randNum;
};

