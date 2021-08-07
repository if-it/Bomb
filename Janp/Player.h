#pragma once
#include "MapColl.h"
#include"Load.h"
#include"BombMana.h"
#include <stdio.h>


#define SPEED 0.2f
#define MAXSPEED 4
#define MAXTEX_X 6
#define MAXTEX_Y 2
#define BOMBVEC 10.0f
#define EXJUMP 10.0f
#define ABILITY_BOMB_SPEED 8.0f

class Player :public MapColl
{
public:
	Player();
	~Player();

	void SaveData_Load(std::vector<std::vector<int>>& map, const int& data_Num);
	void Save_Data_Init(std::vector<std::vector<int>>& map);
	void Init(std::vector<std::vector<int>>& map);
	void Loading(Load* load);
	void Input(Key* key, Controller* con, bool& time);
	void Update(bool& shakeflg, BombMana* bomb);
	void Map_Coll_Update(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage);
	void Save(const int& data_Num);
	void Draw(const Vector2& sc, const Vector2& shake);
	bool Die();
	void Coll();
	void TogeInit();

	int player_mapset;

	void Set_Now_Bomb_Num(const int& num) { now_Bomb_Num = num; }
	int Get_Now_Bomb_Num() { return now_Bomb_Num; }
	int Get_Max_Bomb_Num() { return max_Bomb_Num; }
	int Get_Now_Hp() { return hp; }
	int Get_Max_Hp() { return max_Hp; }
	int& Get_Get_Item() { return get_Item; }
	Vector2 Get_Bomb_Vec() { return bomb_Vec; }
	bool Get_Save_On() { return save_On; }
	bool Get_Toge_Flg() { return toge_flg[4]; }

	GameObject ability1;
private:
	void Move(bool& shakeflg, BombMana* bomb);
	void Blow(const float& blowX, const float& blowY, const bool& lr);
	void Spine();

	int player_Tex[MAXTEX_X * MAXTEX_Y];
	int player_Black_Tex[MAXTEX_X * MAXTEX_Y];


	Vector2 fVec;//êÅÇ¡îÚÇ—
	Vector2 bomb_Vec;
	Vector2 air_Pos;
	Vector2 air_Sc;

	Animation animation;

	Count blow;
	Count invincible;//ñ≥ìG
	Count air_Back_Count;

	bool bomb_Spawn;
	bool move;
	bool one_move_flg;
	bool one_move_flg2;
	bool one_stop_flg;
	bool up;
	bool down;
	bool left;
	bool right;
	bool ability;
	bool ability1_flg;

	int animation_Count_Num;
	int hp;
	int max_Hp;
	int max_Bomb_Num;
	int now_Bomb_Num;
	int damage;
	int air_Count;
	bool bomb_Janp;
	bool air_Array[3];
	bool air;
	float rota_Vec;
	bool save_Coll;
	bool save_On;
	int get_Item;

	//ì_ñ≈
	bool blinking;
	Count blinking_Count;

	struct Save_Data
	{
		int max_Hp;
		int max_Bomb_Num;
		Vector2 pos;
		bool ability1_flg;
		Vector2 sc;
	};

	Save_Data save_Data;

private:
	//Mapä÷òA
	void Map_Coll(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage);
	void MapJub(const int& mapPoint, const int& pointNum, bool& stageChange, int& stage);
	void Animation_Update();
	Vector2 sc2;
	Vector2 vec;
	bool back_flg[5];
	bool coll_flg[5];
	bool toge_flg[5];
	int bxNum[5];
	int byNum[5];
	int item_flg;
};

