#pragma once
#include"MapColl.h"
class MapPlayerColl :public MapColl
{
public:
	MapPlayerColl();
	~MapPlayerColl();
	void Init();
	void MapColl(int(*collMap)[MAPX], Vector2& sc, GameObject& chara,
		int sizeX, int sizeY, int SizeCut, bool &jampFlg, int& playerMapNum, bool& stageChange, int&stage);
	Vector2 sc2;
	bool clear;
private:
	bool bflg[5];
	bool collFlg[5];
	int bxNum[5];
	int byNum[5];
	void MapJub(int mapPoint, GameObject& chara, int XY, bool &jampFlg, int& playerMapNum, bool& stageChange, int&stage);
	Vector2 vec;
	bool jamp;
};

