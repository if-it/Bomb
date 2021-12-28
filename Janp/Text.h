#pragma once
#include "Draw.h"
#include"Load.h"


#define TEX_MAX_NUM 345
class Text :
	public Draw
{
public:
	Text();
	~Text();
	void Init(int& talk_Scene);
	void Loading(Load* load);
	void Update(int& talk_Scene,Controller* con);
	void Draw();

private:
	int tex[TEX_MAX_NUM];
	std::vector<std::vector<int>> texts;
	std::vector<std::vector<GameObject>> text_obj;
};

