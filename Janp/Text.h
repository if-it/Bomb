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
	void Init(int& talk_Scene, Load* load);
	void Loading(Load* load);
	void Update(int& talk_Scene, bool enter,Load* load);
	void Draw();

	bool Get_End() { return end; }
private:
	int text_Tex[TEX_MAX_NUM];
	int chara_Tex;
	std::vector<int> texts;
	std::vector<GameObject> text_obj;
	int count;
	int now_Num;
	int talk_Flg;
	int next;
	bool end;
};

