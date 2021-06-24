#pragma once
#include "Enemy.h"
#include"Load.h"

class Enemy2 :
	public Enemy
{
public:
	Enemy2();
	~Enemy2();

	void Init(std::vector<std::vector<int>>& collMap);
	void Loading(Load* load);
	void Update(const Vector2& pos, Collision* coll);
	void PlayerCahck(const Vector2& pos, Collision* coll);
	void MapCollUpdate(std::vector<std::vector<int>>& collMap);
	void Coll(std::vector<Explosion>& ex);
	void Draw(const Vector2& sc, const Vector2& shake);
private:

	int  enemy2Tex;
	bool spawn;
	bool die;
	bool move;
};

