#pragma once
#include"Explosion.h"
#include"Load.h"
class ExplosionMana :public MapColl
{

public:
	ExplosionMana();
	~ExplosionMana();

	void Init();
	void Loading(Load* load);
	void Update();
	void Map_Coll_Update(int(*collMap)[MAPX]);
	void ExSpawn(GameObject& go);
	void Coll(Collision* coll, ALLVECTOR all, Vector2 size);
	void Draw(const Vector2& sc, const Vector2& shakeconst);

	std::vector<Explosion>ex;
private:
	int exTex[4];
	int exSound;

};

