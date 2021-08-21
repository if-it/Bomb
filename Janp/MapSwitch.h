#pragma once
#include "Draw.h"
#include "Load.h"
class MapSwitch :
	public Draw
{

public:

	MapSwitch();
	~MapSwitch();

	void Init(std::vector<std::vector<int>>& map);
	void Loading(Load* load);
	void Update();
	void Coll(bool& switch_on);
	void Draw(const Vector2& sc, const Vector2& shake);

	std::vector< GameObject> mapSwitch;
private:
	int tex[2];
	int ani;
	Count one_Coll;
};

