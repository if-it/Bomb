#pragma once
#include"GameInclude.h"
class Game:public GameInclude
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
	void Play_Scene_Update();
	void Main_Play_Update();
	void Map_Coll_Update();
	void Obj_Coll_Update();
	void PlayDraw(const Vector2& sc2, const Vector2& shake2);
	Count sceneCount;
};

