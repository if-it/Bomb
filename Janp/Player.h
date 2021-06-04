#pragma once
#include "MapColl.h"
#include"Load.h"
#define SPEED 0.2f
#define JAMP 5.5f
#define MAXSPEED 4
class Player :public MapColl
{
public:
	Player();
	~Player();

	void Init(int(*map)[MAPX]);
	void Loading(Load* load);
	void Update(Key* key, Controller*con, bool &shakeflg);
	void Map_Coll_Update(int(*collMap)[MAPX], Vector2& sc, bool& stageChange, int& stage);
	void Draw(const Vector2& sc, const Vector2& shake);

	int player_mapset;

private:
	int tex[6];

	ANIMATION ani;
	void Input(Key* key, Controller*con);
	void Move(bool &shakeflg, Controller * con);
	bool left;
	bool right;
	bool shot;
private:
	//Map�֘A
	void Map_Coll(int(*collMap)[MAPX], Vector2& sc, bool& stageChange, int& stage);
	void MapJub(const int& mapPoint,int pointNum, bool& stageChange, int& stage);
	Vector2 sc2;
	Vector2 vec;
	bool back_flg[5];
	bool collFlg[5];
	int bxNum[5];
	int byNum[5];
};

