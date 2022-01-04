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
	void TitleInit();
	void Loading(Load* load);
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);

	int tex;
private:
	std::vector< GameObject> dust;
	int mapX;
	int mapY;
};

