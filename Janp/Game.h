#pragma once
#include"GameInclude.h"
#define MAP_F 300
class Game :public GameInclude
{
	using Vector2 = vector::Vector2;
public:
	Game();
	~Game();
	void SystemInit();
	void FirstInit();
	void Init();
	bool Loading();
	void Update();
	void Draw();

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

	struct Option_Data
	{
		int BGM_Volume;
		int SE_Volume;
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
};

