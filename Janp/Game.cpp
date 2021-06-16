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
	/*delete mapExColl;
	delete mapBombColl;*/
	delete particleMana;
	delete bombMana;
	delete playerBombMana;
	delete exMana;

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
	fuse->Init(map->map);
	bombMana->Init();
	shake = Vector2();
	sceneCount = Count();
	particleMana->Init();
	exMana->Init();
	playerBombMana->Init();
}

bool Game::Loading()
{
	if (loadCount > 0)return true;
	loadCount++;

	player->Loading(load);
	bombMana->Loading(load);
	playerBombMana->Loading(bombMana->GetBombSound(), bombMana->GetBombTex());
	load->LoadTex("Load/Texture/Box.png", particleMana->boxTex);
	exMana->Loading(load, particleMana->boxTex);

	load->LoadAnimeTex("Load/Texture/Map.png", 10, 10, 1, SIZE, SIZE, map->tex);
	load->LoadAnimeTex("Load/Texture/BBlock.png", 10, 10, 1, SIZE * 2, SIZE * 2, map->Btex);
	load->LoadAnimeTex("Load/Texture/LineFuse.png", 12, 12, 1, SIZE, SIZE, fuse->lineTex);
	load->LoadAnimeTex("Load/Texture/CurveFuse.png", 12, 12, 1, SIZE, SIZE, fuse->curveTex);
	load->LoadAnimeTex("Load/Texture/WFuse.png", 12, 12, 1, SIZE, SIZE, fuse->wTex);
	load->LoadTex("Load/Texture/Cannon.png", fuse->cannonTex);
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
		PlayUpdate();
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
			scene = PLAY;
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
	if (key->KeyTrigger(KEY_INPUT_1))
	{
		titleFlg = true;
	}
	if (titleFlg)
	{
		if (SceneChangeAdd(5))
		{
			scene = TITLE;
		}
	}
}

void Game::PlayUpdate()
{
	//Update
	map->Update();
	player->SetNowBombNum(playerBombMana->NowBombNum());
	player->Update(key, con, bombShake.flg,playerBombMana);
	fuse->Update(map->map, bombMana);
	bombMana->Update(bombShake.flg, con,exMana);
	playerBombMana->Update(bombShake.flg, con, exMana);
	exMana->Update();
	particleMana->Update();

	//Map当たり判定
	player->Map_Coll_Update(map->map, sc, stageChange, stage);
	bombMana->Coll(coll, player->game_object.allVec, player->game_object.size, bombShake.flg, con,exMana);
	playerBombMana->Coll(coll, player->game_object.allVec, player->game_object.size, bombShake.flg, con, exMana);
	bombMana->MapCollUpdate(map->map);
	playerBombMana->MapCollUpdate(map->map);
	exMana->Map_Coll_Update(map->map);

	//オブジェクト当たり判定
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		fuse->Coll(coll, exMana->ex[i].game_object);
	}

	if (stageChange)
	{
		scene = MAPSET;
	}
	//if (mapPlayerColl->clear)
	//{
	//	scene = GAMECLEAR;
	//}
	Shake(bombShake, 7, Vector2((float)(GetRand(14) - GetRand(14)), (float)(GetRand(8) - GetRand(8))));
	
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
	map->Draw(sc2, shake2);
	fuse->Draw(sc2, shake2);

	player->Draw(sc2, shake2);
	bombMana->Draw(sc2, shake2);
	playerBombMana->Draw(sc2, shake2);
	particleMana->Draw(sc2, shake2);
	exMana->Draw(sc2, shake2);
}
