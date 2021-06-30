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

	GameObject arm;
	GameObject body;
private:
	int tex;
	int  enemy2Tex[21];
	int attackTex[7];
	bool spawn;
	bool die;
	bool move;
	Count attack;
	Animation ani;
	Animation attackAni;
};

