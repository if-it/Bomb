#pragma once
#include "MapColl.h"
#include"Load.h"
#include"BombMana.h"
#define SPEED 0.2f
#define MAXSPEED 4
#define MAXTEX 6
#define BOMBVEC 10.0f
#define EXJUMP 10.0f

class Player :public MapColl
{
public:
	Player();
	~Player();

	void Init(std::vector<std::vector<int>>& collMap);
	void Loading(Load* load);
	void Update(Key* key, Controller* con, bool& shakeflg, BombMana* bomb);
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage);
	void Draw(const Vector2& sc, const Vector2& shake);
	bool Die();
	void Coll();

	int player_mapset;

	void SetNowBombNum(const int& num) { nowBombNum = num; }

private:
	int tex[MAXTEX];
	Vector2 fVec;//�������
	ANIMATION ani;
	void Input(Key* key, Controller* con);
	void Move(bool& shakeflg, Controller* con, BombMana* bomb);
	void Blow(const float &blowX, const float& blowY, const bool& lr);
	bool left;
	bool right;
	bool shot;
	Count blow;
	Count invincible;//���G
	int hp;
	int maxHp;
	int maxBombNum;
	int nowBombNum;
	int damage;
private:
	//Map�֘A
	void Map_Coll(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage);
	void MapJub(const int& mapPoint, const int& pointNum, bool& stageChange, int& stage);
	Vector2 sc2;
	Vector2 vec;
	bool back_flg[5];
	bool collFlg[5];
	int bxNum[5];
	int byNum[5];
};

