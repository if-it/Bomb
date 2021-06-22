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
	stage = 1;
	player->player_mapset = 50;
	Init();
}

void Game::Init()
{
	stageChange = false;
	titleFlg = false;
	title_To_Play = false;
	bombShake = Count();
	map->Init(stage);


	player->Init(map->map);
	enemy1Mana->Init(map->map);
	enemy2->Init(map->map);
	fuse->Init(map->map);


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

	player->Loading(load);
	bombMana->Loading(load);
	exMana->Loading(load);
	enemy1Mana->Loading(load);
	fuse->Loading(load);

	load->LoadAnimeTex("Load/Texture/Map.png", 10, 10, 1, SIZE, SIZE, map->tex);
	load->LoadAnimeTex("Load/Texture/BBlock.png", 10, 10, 1, SIZE * 2, SIZE * 2, map->Btex);
	
	load->LoadTex("Load/Texture/haikei.png", haikei);
	load->LoadTex("Load/Texture/clear.png", clear);
	load->LoadTex("Load/Texture/BombBombBang.png", title);
	load->LoadTex("Load/Texture/Button.png", button);
	load->LoadTex("Load/Texture/Stick.png", stick);


	load->LoadSound("Load/Sound/BGM/Castle.wav", bgm1);

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
			titleFlg = true;
			if (!debug_mode_flg)PlaySoundMem(bgm1, DX_PLAYTYPE_LOOP, true);
			scene = PLAYINIT;
			stage = 0;
			player->player_mapset = 35;
			Init();
		}
		break;
	case TITLE:
		if (titleFlg && SceneChangeSeb(8))
		{
			titleFlg = false;
		}
		if (!titleFlg && !title_To_Play && (con->TrlggerBotton(con->A) || key->KeyTrigger(KEY_INPUT_SPACE) || key->KeyTrigger(KEY_INPUT_UP)))
		{
			title_To_Play = true;
		}
		if (title_To_Play)
		{
			if (SceneChangeAdd(5))
			{
				scene = PLAYINIT;
				stage = 1;
				player->player_mapset = 50;
				Init();
			}
		}
		break;
	case PLAYINIT:
		if (SceneChangeSeb(8))
		{
			scene = PLAY;
		}
		break;
	case PLAY:
		Play_Scene_Update();
		break;
	case MAPSET:
		if (SceneChangeAdd(5))
		{
			Init();
			scene = MAPSET2;
		}
		break;
	case MAPSET2:
		if (SceneChangeSeb(8))
		{
			titleFlg = true;
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
	if (debug_mode_flg && key->KeyTrigger(KEY_INPUT_1))
	{
		scene = PLAYINIT;
	}
	if (titleFlg)
	{
		if (SceneChangeAdd(5))
		{
			scene = TITLE;
		}
	}
}

void Game::Play_Scene_Update()
{
	//Update
	Main_Play_Update();

	//layerチェック

	enemy1Mana->MoveChack(player->game_object.game.allVec.pos, coll);

	//Map当たり判定
	Map_Coll_Update();

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
	//if (mapPlayerColl->clear)
	//{
	//	scene = GAMECLEAR;
	//}
	Shake(bombShake, 4, Vector2((float)(GetRand(10) - GetRand(10)), (float)(GetRand(8) - GetRand(8))));

}

void Game::Main_Play_Update()
{
	map->Update();
	player->SetNowBombNum(bombMana->NowPlayerBombNum());
	player->Update(key, con, bombShake.flg, bombMana);
	enemy1Mana->Update();
	bombMana->Update(bombShake.flg, con, exMana);
	enemy2->Update();

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
	coll_List.push_back(&player->game_object);
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		coll_List.push_back(&exMana->ex[i].game_object);
	}
	for (int i = 0; i < (int)bombMana->bomb.size(); ++i)
	{
		coll_List.push_back(&bombMana->bomb[i].game_object);
	}
	for (int i = 0; i < (int)enemy1Mana->enemy1.size(); ++i)
	{
		coll_List.push_back(&enemy1Mana->enemy1[i].game_object);
	}
	coll_List.push_back(&enemy2->game_object);
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
				coll_List[i]->coll_Obj_List.push_back(&coll_List[n]->game);
			}

		}
	}

	//当たり判定
	player->Coll();
	//爆発とひも
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		fuse->Coll(coll, exMana->ex[i].game_object);
	}
	bombMana->Coll(bombShake.flg, con, exMana);


	enemy1Mana->Coll(exMana->ex);
	enemy2->Coll(exMana->ex);
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
	case PLAY:
	case MAPSET:
	case MAPSET2:
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

	//オブジェクト関連
	enemy1Mana->Draw(sc2, shake2);
	enemy2->Draw(sc2, shake2);
	player->Draw(sc2, shake2);
	bombMana->Draw(sc2, shake2);

	//エフェクト関連
	exMana->Draw(sc2, shake2);
}
