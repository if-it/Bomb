#pragma once
#include"Explosion.h"
#include"Load.h"
#include"Collision.h"
#define EXTEXNUM 12

class ExplosionMana :public MapColl
{

public:
	ExplosionMana();
	~ExplosionMana();

	void Init();
	void Loading(Load* load);
	void Update();
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap, BlockParticleMana* blockParticleMana);
	void ExSpawn(GameObject& go, const int& damage);
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size);
	void Se_Volume(int volume);
	void Draw(const Vector2& sc, const Vector2& shakeconst);

	std::vector<Explosion>ex;
private:
	int NowExNum();
	int exTex[EXTEXNUM];
	int exSound;
	int boxTex;
};

