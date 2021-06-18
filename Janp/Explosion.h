#pragma once
#include "MapColl.h"
#include"Collision.h"
#define EXNUM 8

class Explosion :public MapColl
{
public:
	Explosion();
	~Explosion();
	void Init();
	void Update();
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap);
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size);
	void Draw(const Vector2& sc, const Vector2& shakeconst, const int* exTex, const int& box);

	int damage;
private:

	ANIMATION exAni;
	void Map_Coll(std::vector<std::vector<int>>& collMap);
	void MapJub(const int& mapPoint, const int& pointNum, std::vector<std::vector<int>>& collMap);

	int xNum[9];
	int yNum[9];
	bool spawn;
	int time;
	GameObject exs[EXNUM];
	std::vector<GameObject>boxObj;
	std::vector<int>boxTime;
	std::vector<bool>boxFlg;
};

