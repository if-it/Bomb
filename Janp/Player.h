#pragma once
#include "MapColl.h"
#include"Load.h"
#include"BombMana.h"
#define SPEED 0.2f
#define JAMP 7.5f
#define MAXSPEED 4
#define MAXTEX 6
#define BOMBVEC 10.0f
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


	int player_mapset;

	void SetNowBombNum(const int& num) { nowBombNum = num; }

private:
	int tex[MAXTEX];

	ANIMATION ani;
	void Input(Key* key, Controller* con);
	void Move(bool& shakeflg, Controller* con, BombMana* bomb);
	bool left;
	bool right;
	bool shot;
	int maxBombNum;
	int nowBombNum;
private:
	//MapŠÖ˜A
	void Map_Coll(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage);
	void MapJub(const int& mapPoint, const int& pointNum, bool& stageChange, int& stage);
	Vector2 sc2;
	Vector2 vec;
	bool back_flg[5];
	bool collFlg[5];
	int bxNum[5];
	int byNum[5];
};

