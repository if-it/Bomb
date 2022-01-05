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
	void Update(int& talk_Scene, bool enter, Load* load, const bool& get_controller_flg);
	void Draw();

	bool Get_End() { return end; }
private:
	int text_Tex[TEX_MAX_NUM];
	int chara_Tex[2];
	int text_Back_Tex;
	int text_Next_Tex[2];
	std::vector<int> texts;
	std::vector<GameObject> text_obj;
	int count;
	int now_Num;
	int talk_Flg;
	int next;
	bool end;
	int con_Flg;
	bool enter_Flg;
	Count enter_Count;
	Vector2 enter_Pos;
	int animation[2];
	Animation ani;
};

