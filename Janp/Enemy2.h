#pragma once
#include "Enemy.h"
#include"Load.h"
#include"RockAttackMana.h"
#include"ExplosionMana.h"
#define MAX_HP 200

class Enemy2 :
	public Enemy
{
public:
	Enemy2();
	~Enemy2();

	void Init(std::vector<std::vector<int>>& collMap, Load* load);
	void Update(const Vector2& pos, Collision* coll, bool& shake_flg, const Vector2& sc, RockAttackMana* rockAttackMana, ExplosionMana* ex);
	void PlayerCahck(const Vector2& pos, Collision* coll);
	void MapCollUpdate(std::vector<std::vector<int>>& collMap);
	void Coll(std::vector<Explosion>& ex);
	void Draw(const Vector2& sc, const Vector2& shake);

	bool Get_Ex_End() { return ex_End; }
	int Get_Ex_On() { return ex_on; }

	GameObject arm;
	GameObject body;
private:

	void Map_Coll(std::vector<std::vector<int>>& collMap);
	void MapJub(const int& mapPoint, const int& pointNum);

	int tex;
	int  enemy2Tex[21];
	int attackTex[7];
	int daipanSE;

	int rock_Num;
	int rock_Max_Num;
	bool spawn;
	bool die;
	bool move;
	bool uturn[2];
	bool ex_End;
	int ex_on;
	bool first_Attack;//最初の攻撃判定
	Count attack_Fist_Time;//近づいてから攻撃までの時間
	Count attack_End_Time;//攻撃が終わってからのクールタイム
	Count rush_Time;//突進時間
	Count attack_Second_Time;//攻撃がなかなか当たらないときや攻撃を繰り返す
	Count die_Ex;
	int die_Ex_Num;
	int die_Ex_Max_Num;
	int attack_Animetion_flg;//攻撃を始める
	bool attack_front_flame;//前フレームAttackフラグがonだったか
	Animation ani;
	Animation attackAni;
};

