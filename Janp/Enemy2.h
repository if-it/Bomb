#pragma once
#include "Enemy.h"
#include"Load.h"

class Enemy2 :
	public Enemy
{
public:
	Enemy2();
	~Enemy2();

	void Init(std::vector<std::vector<int>>& collMap, Load* load);
	void Update(const Vector2& pos, Collision* coll);
	void PlayerCahck(const Vector2& pos, Collision* coll);
	void MapCollUpdate(std::vector<std::vector<int>>& collMap);
	void Coll(std::vector<Explosion>& ex);
	void Draw(const Vector2& sc, const Vector2& shake);

	GameObject arm;
	GameObject body;
private:

	void Map_Coll(std::vector<std::vector<int>>& collMap);
	void MapJub(const int& mapPoint, const int& pointNum);

	int tex;
	int  enemy2Tex[21];
	int attackTex[7];
	bool spawn;
	bool die;
	bool move;
	bool uturn[2];
	Count attack_Time;//近づいてから攻撃までの時間
	Count attack_End_Time;//攻撃が終わってからのクールタイム
	Count rush_Time;//突進時間
	int attack_Animetion_flg;//攻撃を始める
	bool attack_front_flame;//前フレームAttackフラグがOnだったか
	Animation ani;
	Animation attackAni;
};

