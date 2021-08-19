#pragma once
#include "Draw.h"
#include"Load.h"
#include"MapBomb.h"

class MapBombMana :
	public Draw
{

public:
	MapBombMana();
	~MapBombMana();

	void Init(std::vector<std::vector<int>>& map);
	void Loading(Load* load);
	void Update();
	void Coll(bool& shakeflg, Controller* con, const bool& switch_on);
	void Coll_End_Set(ExplosionMana* ex);
	void Draw(const Vector2& sc, const Vector2& shake);

	std::vector<MapBomb> mapBomb;
private:
	int tex[8];
};

