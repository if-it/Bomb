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
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size, bool& shakeflg, Controller* con, const int& exSound);
	void Draw(const Vector2& sc, const Vector2& shakeconst, const int* bombTex);

	ANIMATION exAni;

};

