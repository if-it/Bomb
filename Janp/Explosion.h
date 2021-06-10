#pragma once
#include "MapColl.h"
class Explosion :public MapColl
{
public:
	Explosion();
	~Explosion();
	void Init();
	void Update();
	void Map_Coll_Update(int(*collMap)[MAPX]);
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size);
	void Draw(const Vector2& sc, const Vector2& shakeconst, const int* exTex);

	ANIMATION exAni;

private:
	void Map_Coll(int(*collMap)[MAPX]);
	void MapJub(const int& mapPoint, const int& pointNum, int(*collMap)[MAPX]);

	int xNum[9];
	int yNum[9];

};

