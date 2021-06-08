#pragma once
#pragma once
#include"MapColl.h"
#define BSPEED 10.0f
#define EXJUMP 9.0f
class Bomb :public MapColl
{
public:
	Bomb();
	~Bomb();
	void Init();
	void Update(bool& shakeflg, Controller* con);
	void Map_Coll_Update(int(*collMap)[MAPX]);
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size, bool& shakeflg, Controller* con, const int& exSound);
	void Draw(const Vector2& sc, const Vector2& shakeconst, const int* bombTex);


	GameObject ex;
	ANIMATION bombAni;
	ANIMATION exAni;
	int time;
	bool exFlg;


private:

	void Map_Coll(int(*collMap)[MAPX]);
	void MapJub(const int& mapPoint, const int& pointNum);

	void exSpawn(bool& shakeflg, const int& exSound);

};

