#pragma once
#include "Draw.h"
#include"Load.h"
class Dust :
	public Draw
{
public:
	Dust();
	~Dust();

	void Init(std::vector<std::vector<int>>& map, const int& stage);
	void Loading(Load* load);
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);

private:
	std::vector< GameObject> dust;
	int tex;
	int mapX;
	int mapY;
};

