#pragma once
#include"GameInclude.h"
#define MAP_F 300
#define MAP_P_F 35
class Game :public GameInclude
{
	using Vector2 = vector::Vector2;
public:
	Game();
	~Game();
	void SystemInit();
	void FirstInit();
	void Init();
	void TitleInit();
	bool Loading();
	void Update();
	void Draw();

	bool Enter();

	bool game_end_flg = false;
	bool debug_mode_flg = false;

private:
	void Stage_Init();
	void Meta_Data_Init();
	void Play_Scene();
	void Play_Scene_Update();
	void Map_Coll_Update();
	void Obj_Coll_Update();
	void PlayDraw(const Vector2& sc2, const Vector2& shake2);
	void Delete_Data();
	void Option_Data_Save();
	void Data_Load();
	void Save();
	Count sceneCount;
	bool time;
	bool flame_time;
	int data_Num;
	int title_Pal;

	int game_end_set;
	int title_Cursor;
	Vector2 cursor_Pos;
	Vector2 cursor_lerp;
	bool game_end_on;

	Vector2 title_Pos;
	Vector2 text_Play_Pos;
	Vector2 text_Exit_Pos;

	struct Option_Data
	{
		int BGM_Volume;
		int SE_Volume;
		bool con_shake;
	};
	Option_Data option_Data;
	struct Meta_Data
	{
		int stage;
		int save_Count;
	};
	Meta_Data meta_Data;
	Count hetStop;
	bool controller_on;
	int ending_Flg;
	int selectSE;
	int ketteiSE;
	int reset_con;
};

