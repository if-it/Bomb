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
	void Update(int& talk_Scene, bool enter);
	void Draw();

	bool Get_End() { return end; }
private:
	int tex[TEX_MAX_NUM];
	std::vector<int> texts;
	std::vector<GameObject> text_obj;
	int count;
	int now_Num;
	int talk_Flg;
	int next;
	bool end;
};

