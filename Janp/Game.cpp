#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
	delete con;
	delete key;
	delete mouse;

	delete map;
	delete player;
	delete coll;
	delete fuse;

	delete bombMana;
	delete exMana;
	delete enemy1Mana;
	delete enemy2;
	delete ui;
	delete save;
	coll_List.clear();
	InitGraph();
	InitSoundMem();
}

void Game::SystemInit()
{
	// マウスを表示状態にする？
	SetMouseDispFlag(TRUE);

	//コントローラーしか使えない？
	ControllerOn(false);

}



void Game::FirstInit()
{
	ParentInit();
	//コントローラー振動ONOFF
	con->Set_Shake_On(false);
	game_end_flg = false;
	debug_mode_flg = true;
	scene = OPENING;
	stage = 0;
	player->player_mapset = 35;
	Init();
	time = false;
	data_Num = 0;

	option_Data = { 0,0 };
	meta_Data = { 0,0 };
}

void Game::Init()
{
	time = false;
	stageChange = false;
	title_To_Play = false;
	bombShake = Count();

	map->Init(stage);


	player->Init(map->map);
	enemy1Mana->Init(map->map);
	enemy2->Init(map->map);
	fuse->Init(map->map);
	save->Init(map->map);
	ui->Init();

	bombMana->Init();
	shake = Vector2();
	sceneCount = Count();
	exMana->Init();
	coll_List.clear();
}

bool Game::Loading()
{
	if (loadCount > 0)return true;
	loadCount++;

	map->Loading(load);
	player->Loading(load);
	bombMana->Loading(load);
	exMana->Loading(load);
	enemy1Mana->Loading(load);
	fuse->Loading(load, map->Get_Map_Tex());
	enemy2->Loading(load);
	ui->Loading(load);
	save->Loading(load);

	load->LoadTex("Load/Texture/haikei.png", haikei);
	load->LoadTex("Load/Texture/clear.png", clear);
	load->LoadTex("Load/Texture/BombBombBang.png", title);
	load->LoadTex("Load/Texture/Button.png", button);
	load->LoadTex("Load/Texture/Stick.png", stick);


	load->LoadSound("Load/Sound/BGM/Castle.wav", bgm1);

	FILE* fp;

	if (fopen_s(&fp, "Load/Data/SaveData/Option/Option_Data.dat", "r") == 0)
	{
		fread_s(&option_Data, sizeof(option_Data), sizeof(option_Data), 1, fp);
		fclose(fp);
	}
	else
	{
		option_Data = { 100,100 };
	}


	if (loadCount >= 0)return true;
	return false;
}





void Game::Update()
{
	key->Input();
	con->Input();
	switch (scene)
	{
	case OPENING:
		SetBackgroundColor(0xEF, 0xFF, 0xEF);
		scene = LOAD;
		break;
	case LOAD:
		if (Loading())
		{
			Init();
			if (!debug_mode_flg)
			{
				PlaySoundMem(bgm1, DX_PLAYTYPE_LOOP, true);
				titleFlg = true;
			}
			else
			{
				titleFlg = false;
				scene = PLAYINIT;
				Data_Load();//デバック用
			}
		}
		break;
	case TITLE:
		if (titleFlg && SceneChangeSeb(8))
		{
			titleFlg = false;
		}
		if (!titleFlg && !title_To_Play)
		{
			if ((con->TrlggerBotton(con->A) || key->KeyTrigger(KEY_INPUT_SPACE) || key->KeyTrigger(KEY_INPUT_UP)))title_To_Play = true;

			if (key->KeyTrigger(KEY_INPUT_A))Delete_Data();
		}
		if (title_To_Play)
		{
			if (SceneChangeAdd(5))
			{
				scene = PLAYINIT;
				Data_Load();
			}
		}
		break;
	case PLAYINIT:
		if (SceneChangeSeb(8))
		{
			scene = PLAY;
		}
		break;
	case PLAYINIT2:
		if (SceneChangeAdd(5))
		{
			scene = PLAYINIT;
			player->TogeInit();
		}
		break;
	case PLAY:
		Play_Scene();
		break;
	case MAPSET:
		if (SceneChangeAdd(5))
		{
			Init();
			scene = PLAYINIT;
		}
		break;
	case GAMECLEAR:
		if (con->TrlggerBotton(con->A) || key->KeyTrigger(KEY_INPUT_SPACE) || key->KeyTrigger(KEY_INPUT_UP))
		{
			titleFlg = true;
		}
		break;
	default:
		break;
	}
	if (debug_mode_flg)
	{
		if (key->KeyTrigger(KEY_INPUT_1))
		{
			scene = MAPSET;
		}
		if (key->KeyTrigger(KEY_INPUT_2))
		{
			titleFlg = true;
		}
	}
	if (titleFlg)
	{
		if (SceneChangeAdd(5))
		{
			scene = TITLE;
			Init();
		}
	}
}

void Game::Data_Load()
{

	FILE* fp;

	std::string fileNama;
	switch (data_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Meta/Meta_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Meta/Meta_Data.dat";
		break;
	}

	if (fopen_s(&fp, fileNama.c_str(), "r") == 0)
	{
		fread_s(&meta_Data, sizeof(meta_Data), sizeof(meta_Data), 1, fp);
		fclose(fp);
	}
	else
	{
		Meta_Data_Init();
	}

	map->Save_Date_Load(data_Num, stage);

	player->SaveData_Load(map->map, data_Num);
}

void Game::Meta_Data_Init()
{
	if (debug_mode_flg) stage = 0;
	else stage = 1;

	meta_Data = { stage,0 };
}

void Game::Delete_Data()
{
	Meta_Data_Init();

	map->Save_Data_Init(stage);
	player->Player_Save_Date_Init(map->map);

	Save();
}

void Game::Option_Data_Save()
{
	FILE* fp;
	if (fopen_s(&fp, "Load/Data/SaveData/Option/Option_Data.dat", "w") == 0)
	{
		fwrite(&option_Data, sizeof(option_Data), 1, fp);
		fclose(fp);
	}
	else
	{
		MessageBox(NULL, "Option", "SaveDataのエラー", MB_OK);
	}
}

void Game::Save()
{

	Option_Data_Save();
	std::string fileNama;
	switch (data_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Meta/Meta_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Meta/Meta_Data.dat";
		break;
	}
	FILE* fp;
	if (fopen_s(&fp, fileNama.c_str(), "w") == 0)
	{
		meta_Data.save_Count++;
		fwrite(&meta_Data, sizeof(meta_Data), 1, fp);
		fclose(fp);
	}
	else
	{
		MessageBox(NULL, "Meta", "SaveDataのエラー", MB_OK);
	}

	map->Save(data_Num);

	player->Save(data_Num);
}

void Game::Play_Scene()
{
	flame_time = time;
	if (!player->Get_Save_On())
	{

		//入力
		player->Input(key, con, time);

		if (!time)
		{

			//Update
			Play_Scene_Update();

			//layerチェック

			enemy1Mana->MoveChack(player->game_object.game.allVec.pos, coll);

			//Map当たり判定
			Map_Coll_Update();

		}
		//オブジェクト当たり判定
		Obj_Coll_Update();
		if (player->Die())
		{
			titleFlg = true;
		}
		if (stageChange)
		{
			scene = MAPSET;
		}
		if (player->Get_Toge_Flg())
		{
			scene = PLAYINIT2;
		}

		if (!time)
		{
			Shake(bombShake, 4, Vector2((float)(GetRand(12) - GetRand(12)), (float)(GetRand(8) - GetRand(8))));
			ui->Update(player->Get_Now_Hp(), player->Get_Now_Bomb_Num(),player->Get_Max_Hp(),player->Get_Max_Bomb_Num());
		}
	}
	else
	{
		Save();
	}
}

void Game::Play_Scene_Update()
{
	map->Update();
	player->Set_Now_Bomb_Num(bombMana->NowPlayerBombNum());
	player->Update(bombShake.flg, bombMana);
	enemy1Mana->Update();
	bombMana->Update(bombShake.flg, con, exMana, time, flame_time, player->Get_Bomb_Vec());
	enemy2->Update(player->game_object.game.allVec.pos, coll);
	save->Update();

	fuse->Update(map->map, bombMana);
	exMana->Update();

}

void Game::Map_Coll_Update()
{
	player->Map_Coll_Update(map->map, sc, stageChange, stage);
	bombMana->MapCollUpdate(map->map);
	enemy1Mana->MapCollUpdate(map->map);
	enemy2->MapCollUpdate(map->map);

	exMana->Map_Coll_Update(map->map);
}

void Game::Obj_Coll_Update()
{
	//GameObjectリストの初期化
	coll_List.clear();
	//GameObjectリストにGameObjectの追加

	//player
	coll_List.push_back(&player->game_object);

	//アビリティ
	coll_List.push_back(&player->ability1);

	//爆発
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		coll_List.push_back(&exMana->ex[i].game_object);
	}
	//爆弾
	for (int i = 0; i < (int)bombMana->bomb.size(); ++i)
	{
		coll_List.push_back(&bombMana->bomb[i].game_object);
	}
	//Enemy1
	for (int i = 0; i < (int)enemy1Mana->enemy1.size(); ++i)
	{
		coll_List.push_back(&enemy1Mana->enemy1[i].game_object);
	}
	//Enemy2
	coll_List.push_back(&enemy2->game_object);
	coll_List.push_back(&enemy2->body);
	coll_List.push_back(&enemy2->arm);

	//Saveポイント
	coll_List.push_back(&save->game_object);

	//当たり判定リストに当たっている物を追加
	for (int i = 0; i < (int)coll_List.size(); ++i)
	{
		coll_List[i]->coll_Obj_List.clear();
		coll_List[i]->game.nameTag;
		if (coll_List[i]->same) { continue; }
		for (int n = 0; n < (int)coll_List.size(); ++n)
		{
			if (i == n || coll_List[n]->same) { continue; }

			if (coll->CollsionObj(*coll_List[i], *coll_List[n]))
			{
				coll_List[n]->game.nameTag;
				coll_List[i]->coll_Obj_List.push_back(&coll_List[n]->game);
				if (coll_List[i]->coll_Obj_List.size() >= 3)
				{
					coll_List[n]->game.nameTag;
				}
			}

		}
	}
	enemy1Mana->Chack();
	//当たり判定
	player->Coll();
	//爆発とひも
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		fuse->Coll(coll, exMana->ex[i].game_object);
	}

	enemy1Mana->Coll(exMana->ex);
	bombMana->Coll(bombShake.flg, con);
	enemy2->Coll(exMana->ex);

	//全ての当たり判定が終了したら結果に応じてオブジェクトを生成

	bombMana->Coll_End_Set(exMana);

}



void Game::Draw()
{
	DrawGraph(0, 0, haikei, true);
	switch (scene)
	{
	case OPENING:
		break;
	case LOAD:
		break;
	case TITLE:
		DrawBox(0, 0, WIDTH, HEIGHT, GetColor(160, 160, 160), true);
		DrawGraph(0, 0, title, true);
		DrawGraph(WIDTH / 2, HEIGHT - SIZE * 3, button, true);
		break;
	case PLAYINIT:
	case PLAYINIT2:
	case PLAY:
	case MAPSET:
		PlayDraw(sc, shake);
		break;
	case GAMECLEAR:
		PlayDraw(sc, shake);
		DrawGraph(-80, -102, clear, true);
		break;
	default:
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	Box(Vector2(), GetColor(0, 0, 0), drawScene, true, Vector2(), Vector2(), WIDTH, HEIGHT);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}





void Game::PlayDraw(const Vector2& sc2, const Vector2& shake2)
{
	//Map関連
	map->Draw(sc2, shake2);
	fuse->Draw(sc2, shake2);
	save->Draw(sc2, shake2);

	//オブジェクト関連
	enemy1Mana->Draw(sc2, shake2);
	enemy2->Draw(sc2, shake2);
	player->Draw(sc2, shake2);
	bombMana->Draw(sc2, shake2);

	//エフェクト関連
	exMana->Draw(sc2, shake2);

	//UI関連
	ui->Draw();
}


