#pragma once
#include "Draw.h"
#include "Load.h"
class UI : public Draw
{
public:
	UI();
	~UI();
	void Init();
	void Loading(Load* load);
	void Update(const int& hp, const int& playerBomb);
	void Draw();

private:
	int heartTex;
	int bombTex;
	int heartNum;
	int bombNum;
};

