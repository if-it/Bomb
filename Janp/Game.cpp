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
	delete saveMana;
	delete itemMana;
	delete backMap;
	delete backMap2;
	delete dust;
	delete mapBombMana;
	delete mapSwitch;

	coll_List.clear();
	InitGraph();
	InitSoundMem();
}

void Game::SystemInit()
{
	// マウスを表示状態にする？
	SetMouseDispFlag(TRUE);

	//コントローラーしか使えない？
	ControllerOnly(false);

}



void Game::FirstInit()
{
	ParentInit();
	//コントローラー振動ONOFF
	con->Set_Shake_On(false);
	game_end_flg = false;
	debug_mode_flg = true;
	scene = OPENING;
	stage = MAP_F;
	player->player_mapset = MAP_P_F;
	Init();
	time = false;
	data_Num = 0;

	option_Data = { 0,0 };
	meta_Data = { 0,0 };
	controller_on = false;
}

void Game::Init()
{
	time = false;
	stageChange = false;
	title_To_Play = false;
	bombShake = Count();

	map->Init(stage, load);


	itemMana->Init(map->map, stage);

	player->Init(map->map, sc);

	Stage_Init();

	ui->Init();
	bombMana->Init();
	exMana->Init();

	shake = Vector2();
	sceneCount = Count();
	coll_List.clear();

	hetStop = Count();
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
	saveMana->Loading(load);
	itemMana->Loading(load);
	backMap->Loading(load);
	backMap2->Loading(load);
	dust->Loading(load);
	mapBombMana->Loading(load);
	mapSwitch->Loading(load);

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

	if (con->All_Het_Controller())
	{
		controller_on = true;
	}
	if (key->AllHetKey())
	{
		controller_on = false;
	}



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
		if (!hetStop.flg && SceneChangeAdd(5))
		{
			scene = PLAYINIT;
			if (player->Get_Die_End())
			{
				bombMana->Init();
				exMana->Init();

				Data_Load();
			}
			else
			{
				player->TogeInit();
			}
		}
		hetStop.Conuter(10);
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

	stage = meta_Data.stage;


	map->Save_Date_Load(data_Num, stage, load);

	player->SaveData_Load(map->map, data_Num, sc);

	itemMana->SaveData_Load(map->map, data_Num, stage);

	Stage_Init();
}

void Game::Stage_Init()
{
	backMap->Init(stage);
	backMap2->Init(stage, load);
	saveMana->Init(map->map);
	enemy1Mana->Init(map->map);
	enemy2->Init(map->map);
	fuse->Init(map->map);
	dust->Init(map->map, stage);
	mapBombMana->Init(map->map);
	mapSwitch->Init(map->map);
}

void Game::Meta_Data_Init()
{
	stage = MAP_F;

	meta_Data = { stage,0 };
}

void Game::Delete_Data()
{
	Meta_Data_Init();

	map->Save_Data_Init();
	player->Save_Data_Init(map->map, sc);
	itemMana->Save_Data_Init();

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
	saveMana->Save_Mode();

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
	itemMana->Save(data_Num);
}

void Game::Play_Scene()
{
	flame_time = time;
	if (!player->Get_Save_On())
	{

		//入力
		player->Input(key, con, time);
		if (!hetStop.flg)
		{

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
			if (stageChange)
			{
				scene = MAPSET;
			}
			if (player->Get_Toge_Flg() && !player->Die() || player->Get_Die_End())
			{
				scene = PLAYINIT2;
			}

		}
		if (!time)
		{
			Shake(bombShake, 4, Vector2((float)(GetRand(12) - GetRand(12)), (float)(GetRand(8) - GetRand(8))));
			ui->Update(player->Get_Now_Hp(), player->Get_Now_Bomb_Num(), player->Get_Max_Hp(),
				player->Get_Max_Bomb_Num(), player->Get_Get_Guide(), player->game_object.GetPos(),
				controller_on, player->Get_Space_On());
		}
		hetStop.Conuter(8);
	}
	else
	{
		Save();
	}
}

void Game::Play_Scene_Update()
{
	map->Update();
	backMap2->Update(sc);

	player->Set_Now_Bomb_Num(bombMana->NowPlayerBombNum());
	player->Update(bombShake.flg, bombMana);
	enemy1Mana->Update();
	bombMana->Update(bombShake.flg, con, exMana, time, flame_time, player->Get_Bomb_Vec());
	enemy2->Update(player->game_object.game.allVec.pos, coll);

	fuse->Update(map->map, bombMana);
	saveMana->Update();
	itemMana->Update();
	mapBombMana->Update(player->Get_Switch_On());
	mapSwitch->Update();

	exMana->Update();
	dust->Update();

}

void Game::Map_Coll_Update()
{
	player->Map_Coll_Update(map->map, sc, stageChange, stage, hetStop.flg);
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
	for (int i = 0; i < (int)saveMana->save.size(); ++i)
	{
		coll_List.push_back(&saveMana->save[i].game_object);
	}

	//itme
	for (int i = 0; i < (int)itemMana->item.size(); ++i)
	{
		coll_List.push_back(&itemMana->item[i].game_object);
	}

	//MapBomb
	for (int i = 0; i < (int)mapBombMana->mapBomb.size(); ++i)
	{
		coll_List.push_back(&mapBombMana->mapBomb[i].game_object);
	}

	//MapSwitch

	for (int i = 0; i < (int)mapSwitch->mapSwitch.size(); ++i)
	{
		coll_List.push_back(&mapSwitch->mapSwitch[i]);
	}

	//当たり判定リストに当たっている物を追加
	for (int i = 0; i < (int)coll_List.size(); ++i)
	{
		coll_List[i]->coll_Obj_List.clear();
		if (coll_List[i]->same) { continue; }
		for (int n = 0; n < (int)coll_List.size(); ++n)
		{
			if (i == n || coll_List[n]->same) { continue; }

			if (coll->CollsionObj(*coll_List[i], *coll_List[n]))
			{
				coll_List[n]->game.nameTag;
				coll_List[i]->coll_Obj_List.push_back(&coll_List[n]->game);
			}

		}
	}


	//当たり判定
	player->Coll(hetStop.flg);
	//爆発とひも
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		fuse->Coll(coll, exMana->ex[i].game_object);
	}

	enemy1Mana->Coll(exMana->ex);
	bombMana->Coll(bombShake.flg, con);
	enemy2->Coll(exMana->ex);
	saveMana->Coll();
	itemMana->Coll(player->Get_Get_Item());
	mapBombMana->Coll(bombShake.flg, con, player->Get_Switch_On());
	mapSwitch->Coll(player->Get_Switch_On());


	//全ての当たり判定が終了したら結果に応じてオブジェクトを生成

	bombMana->Coll_End_Set(exMana);
	mapBombMana->Coll_End_Set(exMana);

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
	backMap2->Draw(sc2, shake2);
	backMap->Draw(sc2, shake2);
	map->Draw(sc2, shake2);
	fuse->Draw(sc2, shake2);
	saveMana->Draw(sc2, shake2);
	itemMana->Draw(sc2, shake2);
	mapBombMana->Draw(sc2, shake2);
	mapSwitch->Draw(sc2, shake2);

	//オブジェクト関連
	enemy1Mana->Draw(sc2, shake2);
	enemy2->Draw(sc2, shake2);
	player->Draw(sc2, shake2);
	bombMana->Draw(sc2, shake2);

	//エフェクト関連
	exMana->Draw(sc2, shake2);
	dust->Draw(sc2, shake2);


	//UI関連
	ui->Draw(sc2, shake2);
}


