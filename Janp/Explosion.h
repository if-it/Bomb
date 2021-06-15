#pragma once
#include "MapColl.h"
class Explosion :public MapColl
{
public:
	Explosion();
	~Explosion();
	void Init();
	void Update();
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap);
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size);
	void Draw(const Vector2& sc, const Vector2& shakeconst, const int* exTex);

	ANIMATION exAni;

private:
	void Map_Coll(std::vector<std::vector<int>>& collMap);
	void MapJub(const int& mapPoint, const int& pointNum, std::vector<std::vector<int>>& collMap);

	int xNum[9];
	int yNum[9];

};

