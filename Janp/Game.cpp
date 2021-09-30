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
	delete enemy3Mana;
	delete sideBomb;
	delete sideExMana;
	delete enemy4Mana;
	delete rockEffeMana;
	delete rockAttackMana;

	coll_List.clear();
	InitGraph();
	InitSoundMem();
}

void Game::SystemInit()
{
	// �}�E�X��\����Ԃɂ���H
	SetMouseDispFlag(TRUE);

	//�R���g���[���[�����g���Ȃ��H
	ControllerOnly(false);

}



void Game::FirstInit()
{
	ParentInit();
	//�R���g���[���[�U��ONOFF
	con->Set_Shake_On(false);
	game_end_flg = false;
	debug_mode_flg = false;
	scene = OPENING;
	stage = MAP_F;
	player->player_mapset = MAP_P_F;
	Init();
	time = false;
	data_Num = 0;

	option_Data = { 0,0,false };
	meta_Data = { 0,0 };
	controller_on = false;
	TitleInit();
}

void Game::TitleInit()
{
	title_Pal = 0;
	title_Cursor = 0;
	title_Pos = Vector2(WIDTH / 2 - 384, HEIGHT / 2 - 192);
	text_Play_Pos = Vector2(WIDTH + 200, HEIGHT / 2);
	text_Exit_Pos = Vector2(WIDTH + 200, HEIGHT / 2 + 100);

	dust->TitleInit();

	load->LoadTex("Load/Texture/Title.png", title);
	load->LoadTex("Load/Texture/Text_Play.png", text_Play_Tex);
	load->LoadTex("Load/Texture/Text_Exit.png", text_Exit_Tex);
}

void Game::Init()
{

	time = false;
	stageChange = false;
	title_To_Play = false;
	shake_Counter = Count();
	ending_Flg = 0;

	map->Init(stage, load);


	itemMana->Init(map->map, stage);

	player->Init(map->map, sc);
	Stage_Init();

	ui->Init();
	bombMana->Init();
	exMana->Init();
	sideBomb->Init();
	sideExMana->Init();
	rockEffeMana->Init();
	rockAttackMana->Init();

	shake = Vector2();
	sceneCount = Count();
	coll_List.clear();

	hetStop = Count();
	game_end_set = 0;
	cursor_Pos = Vector2();
	cursor_lerp = Vector2();
	game_end_on = false;
	reset_con = 0;
}


bool Game::Loading()
{
	if (loadCount > 0)return true;
	loadCount++;

	map->Loading(load);
	player->Loading(load);
	bombMana->Loading(load);
	exMana->Loading(load);
	fuse->Loading(load, map->Get_Map_Tex());
	ui->Loading(load);
	saveMana->Loading(load);
	itemMana->Loading(load);
	backMap->Loading(load);
	backMap2->Loading(load);
	dust->Loading(load);
	mapBombMana->Loading(load);
	mapSwitch->Loading(load);
	sideBomb->Loading(load);
	sideExMana->Loading(load);
	rockEffeMana->Loading(load);
	rockAttackMana->Loading(load);

	load->LoadTex("Load/Texture/haikei.png", haikei);
	load->LoadTex("Load/Texture/Cursor.png", cursor);


	load->LoadSound("Load/Sound/BGM/Castle.wav", bgm1);

	load->LoadSound("Load/Sound/SE/select.wav", selectSE);
	load->LoadSound("Load/Sound/SE/kettei.wav", ketteiSE);


	FILE* fp;

	if (fopen_s(&fp, "Load/Data/SaveData/Option/Option_Data.dat", "r") == 0)
	{
		fread_s(&option_Data, sizeof(option_Data), sizeof(option_Data), 1, fp);
		fclose(fp);
	}
	else
	{
		option_Data = { 100,100,false };
	}


	if (loadCount >= 0)return true;
	return false;
}





void Game::Update()
{
	key->Input();
	con->Input();
	con->Set_Shake_On(option_Data.con_shake);



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
				//PlaySoundMem(bgm1, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(230, bgm1);
				title_Flg = 1;
			}
			else
			{
				title_Flg = 0;
				scene = PLAYINIT;
				Data_Load();//�f�o�b�N�p
			}
		}
		break;
	case TITLE:
		
		if (title_Flg == 1 && SceneChangeSeb(8))//�Ó]�^�C�g���܂�
		{
			title_Flg = 0;
		}
		if (title_Flg == 0)//�^�C�g���\��
		{
			title_Pal += 3;
			if (title_Pal >= 255)
			{
				title_Pal = 255;

				if (game_end_set == 0)
				{
					title_Flg = 2;//�^�C�g���\���I���
				}
			}
		}
		else if (title_Flg == 2)//�^�C�g�����Ɉړ�
		{
			title_Pos = Vector2::Lerp(title_Pos, Vector2(50, HEIGHT / 2 - 192), 0.03f);
			if (title_Pos.x - 50 <= 5.0f)
			{
				title_Flg = 3;
			}
		}
		else if (title_Flg == 3)//�e�L�X�g�\��
		{
			title_Pos = Vector2::Lerp(title_Pos, Vector2(50, HEIGHT / 2 - 192), 0.03f);
			text_Play_Pos = Vector2::Lerp(text_Play_Pos, Vector2(WIDTH - 400, HEIGHT / 2), 0.05f);
			if (text_Play_Pos.x - (WIDTH - 400) <= 100.0f)
			{
				text_Exit_Pos = Vector2::Lerp(text_Exit_Pos, Vector2(WIDTH - 400, HEIGHT / 2 + 100), 0.05f);
				if (text_Exit_Pos.x - (WIDTH - 400) <= 10.0f)
				{
					title_Flg = 4;
					cursor_Pos = Vector2(text_Play_Pos.x + 15, text_Play_Pos.y - 10);
					cursor_lerp = Vector2(text_Play_Pos.x + 15, text_Play_Pos.y - 10);
				}
			}
		}
		else if (title_Flg == 4 && game_end_set == 0)//�J�[�\���ړ�
		{
			++reset_con;
			if (reset_con == 180)
			{
				ReSetupJoypad();
				reset_con = 0;
			}
			text_Play_Pos = Vector2::Lerp(text_Play_Pos, Vector2(WIDTH - 400, HEIGHT / 2), 0.05f);
			text_Exit_Pos = Vector2::Lerp(text_Exit_Pos, Vector2(WIDTH - 400, HEIGHT / 2 + 100), 0.05f);
			int stickLY = con->StickLTriggerY();
			if (key->KeyTrigger(KEY_INPUT_UP) > 0 || stickLY == 1)
			{
				--title_Cursor;
				PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
				if (title_Cursor < 0)
				{
					title_Cursor = 0;
				}
			}
			if (key->KeyTrigger(KEY_INPUT_DOWN) > 0 || stickLY == -1)
			{
				++title_Cursor;
				PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
				if (title_Cursor > 1)
				{
					title_Cursor = 1;
				}
			}

			if (title_Cursor == 0)
			{
				cursor_lerp = Vector2(text_Play_Pos.x + 15, text_Play_Pos.y - 10);
				if (Enter())title_Flg = 5;
			}
			else if (title_Cursor == 1)
			{
				cursor_lerp = Vector2(text_Exit_Pos.x + 15, text_Exit_Pos.y - 10);
				if (Enter())game_end_set = 1;
				if (key->KeyTrigger(KEY_INPUT_A))Delete_Data();
			}

		}
		if (title_Flg == 5)
		{
			title_Pos = Vector2::Lerp(title_Pos, Vector2(-1000, HEIGHT / 2 - 192), 0.03f);
			text_Play_Pos = Vector2::Lerp(text_Play_Pos, Vector2(WIDTH + 20, HEIGHT / 2), 0.05f);
			text_Exit_Pos = Vector2::Lerp(text_Exit_Pos, Vector2(WIDTH + 20, HEIGHT / 2 + 100), 0.05f);
			if (title_Pos.x < -800)
			{
				title_Flg = 10;
			}
		}
		else if (title_Flg == 6)
		{

		}
		if (title_Flg == 10 && !title_To_Play && game_end_set == 0)//�v���C�V�[���܂ňړ�
		{
			title_Pal = 0;
			title_To_Play = true;
			title_Flg = 0;

		}

		if (title_To_Play)
		{
			if (SceneChangeAdd(5))
			{
				scene = PLAYINIT;
				Data_Load();
				DeleteGraph(title);
				DeleteGraph(text_Play_Tex);
				DeleteGraph(text_Exit_Tex);
			}
		}
		ui->Exit(game_end_set, false);
		dust->Update();
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
				rockEffeMana->Init();
				exMana->Init();
				sideBomb->Init();
				rockAttackMana->Init();
				sideExMana->Init();
				enemy1Mana->Save();
				enemy3Mana->Save();
				enemy4Mana->Save();

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
		if (SceneChangeAdd(18))
		{
			Init();
			scene = PLAYINIT;
		}
		break;
	case GAMECLEAR:
		if (con->TrlggerBotton(con->A) || key->KeyTrigger(KEY_INPUT_SPACE) || key->KeyTrigger(KEY_INPUT_UP))
		{
			title_Flg = 1;
		}
		break;
	case ENDING:
		if (ending_Flg == 0 && SceneChangeSeb(5))ending_Flg = 1;

		if (ending_Flg == 1)ui->Exit(ending_Flg, true);

		if (ending_Flg == 2 && Enter())ending_Flg = 3;

		if (ending_Flg == 3)title_Flg = 1;

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
			title_Flg = 1;
		}
	}
	if (title_Flg == 1)
	{
		if (SceneChangeAdd(5))
		{
			scene = TITLE;
			Init();
			TitleInit();
		}
	}
	if (con->All_Het_Controller())
	{
		controller_on = true;
		con->Set_Shake_On(option_Data.con_shake);
	}
	if (key->AllHetKey())
	{
		controller_on = false;
		con->Set_Shake_On(false);
	}
	if (game_end_set > 0)
	{
		time = true;
	}
	if (game_end_set == 0 && (key->KeyTrigger(KEY_INPUT_ESCAPE) || con->TrlggerBotton(con->BACK)))
	{
		game_end_set = 1;
		//if (debug_mode_flg)game_end_flg = true;
	}
	if (game_end_set == 2)
	{
		cursor_Pos = Vector2(745, 430);
		cursor_lerp = Vector2(745, 430);
		game_end_on = true;
		game_end_set = 3;
	}
	if (game_end_set == 3)
	{
		int stickLX = con->StickLTriggerX();
		if (key->KeyTrigger(KEY_INPUT_RIGHT) || stickLX == 1)
		{
			cursor_lerp = Vector2(745, 430);
			game_end_on = true;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}
		if (key->KeyTrigger(KEY_INPUT_LEFT)  || stickLX == -1)
		{
			cursor_lerp = Vector2(545, 430);
			game_end_on = false;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}
		if (Enter())
		{
			if (!game_end_on)game_end_flg = true;
			else game_end_set = 4;
		}
	}
	cursor_Pos = Vector2::Lerp(cursor_Pos, cursor_lerp, 0.25f);

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
	enemy1Mana->Init(map->map, load, stage);
	enemy2->Init(map->map, load);
	enemy3Mana->Init(map->map, load, stage);
	enemy4Mana->Init(map->map, load, stage);
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
		MessageBox(NULL, "Option", "SaveData�̃G���[", MB_OK);
	}
}

void Game::Save()
{
	saveMana->Save_Mode();
	meta_Data.stage = stage;
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
		MessageBox(NULL, "Meta", "SaveData�̃G���[", MB_OK);
	}

	map->Save(data_Num);

	player->Save(data_Num);
	itemMana->Save(data_Num);

	enemy1Mana->Save();
	enemy3Mana->Save();
	enemy4Mana->Save();
}

void Game::Play_Scene()
{
	flame_time = time;
	if (!player->Get_Save_On())
	{

		//Player�ւ̓���
		if (game_end_set == 0 && enemy2->Get_Ex_On() == 0)
		{
			player->Set_Contorl_Flg(true);
		}
		else
		{
			player->Set_Contorl_Flg(false);
		}
		player->Input(key, con, time);

		if (!hetStop.flg)
		{

			if (!time)
			{

				//Update
				Play_Scene_Update();

				//layer�`�F�b�N

				enemy1Mana->MoveChack(player->game_object.game.allVec.pos, coll);
				enemy4Mana->MoveChack(player->game_object.game.allVec.pos, coll);

				//Map�����蔻��
				Map_Coll_Update();

			}
			//�I�u�W�F�N�g�����蔻��
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
			Shake(shake_Counter, 6, Vector2((float)(GetRand(14) - GetRand(14)), (float)(GetRand(9) - GetRand(9))));
		}
		ui->Update(player->Get_Now_Hp(), player->Get_Now_Bomb_Num(), player->Get_Max_Hp(),
			player->Get_Max_Bomb_Num(), player->Get_Get_Guide(), player->game_object.GetPos(),
			controller_on, player->Get_Space_On(), player->Get_Tutorial_Flg(), player->Get_Move_Guide_On(),
			player->Get_Save_On(), game_end_set);
		hetStop.Conuter(8);

		if (enemy2->Get_Ex_End() && SceneChangeAdd(3))
		{
			scene = ENDING;
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
	backMap2->Update(sc);

	player->Set_Now_Bomb_Num(bombMana->NowPlayerBombNum());
	player->Update(shake_Counter.flg, bombMana, sideBomb);
	enemy1Mana->Update(rockEffeMana);
	enemy3Mana->Update(rockEffeMana);
	enemy4Mana->Update(rockEffeMana);
	bombMana->Update(shake_Counter.flg, con, exMana, time, flame_time, player->Get_Bomb_Vec());
	enemy2->Update(player->game_object.game.allVec.pos, coll, shake_Counter.flg, sc, rockAttackMana, exMana);
	rockAttackMana->Update();
	sideBomb->Update(con);
	sideExMana->Update(sideBomb->Get_Explosion_On(), sideBomb->game_object.GetPos(), map->map, shake_Counter.flg);

	fuse->Update(map->map, bombMana);
	saveMana->Update();
	itemMana->Update();
	mapBombMana->Update(player->Get_Switch_On());
	mapSwitch->Update();

	exMana->Update();
	dust->Update();
	rockEffeMana->Update();

}

void Game::Map_Coll_Update()
{
	player->Map_Coll_Update(map->map, sc, stageChange, stage, hetStop.flg);
	bombMana->MapCollUpdate(map->map);
	enemy1Mana->MapCollUpdate(map->map);
	enemy3Mana->MapCollUpdate(map->map);
	enemy4Mana->MapCollUpdate(map->map);
	enemy2->MapCollUpdate(map->map);

	exMana->Map_Coll_Update(map->map);
	sideBomb->Map_Coll_Update(map->map);
}

void Game::Obj_Coll_Update()
{
	//GameObject���X�g�̏�����
	coll_List.clear();
	//GameObject���X�g��GameObject�̒ǉ�

	//player
	coll_List.push_back(&player->game_object);

	//�A�r���e�B

	//SideBomb
	for (int i = 0; i < (int)sideExMana->sideEx.size(); ++i)
	{
		coll_List.push_back(&sideExMana->sideEx[i].game_object);
	}

	//����
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		coll_List.push_back(&exMana->ex[i].game_object);
	}
	//���e
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

	//RockAttack
	for (int i = 0; i < (int)rockAttackMana->rock_Attack.size(); ++i)
	{
		coll_List.push_back(&rockAttackMana->rock_Attack[i].game_object);
	}

	//Enemy3

	for (int i = 0; i < (int)enemy3Mana->enemy3.size(); ++i)
	{
		coll_List.push_back(&enemy3Mana->enemy3[i].game_object);
	}

	//Enemy4
	for (int i = 0; i < (int)enemy4Mana->enemy4.size(); ++i)
	{
		coll_List.push_back(&enemy4Mana->enemy4[i].game_object);
	}

	//Save�|�C���g
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

	//�����蔻�胊�X�g�ɓ������Ă��镨��ǉ�
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


	//�����蔻��
	player->Coll(hetStop.flg);
	//�����ƂЂ�
	for (int i = 0; i < exMana->ex.size(); ++i)
	{
		fuse->Coll(coll, exMana->ex[i].game_object);
	}

	enemy1Mana->Coll(exMana->ex);
	enemy3Mana->Coll(exMana->ex);
	enemy4Mana->Coll(exMana->ex);
	bombMana->Coll(shake_Counter.flg, con);
	enemy2->Coll(exMana->ex);
	saveMana->Coll();
	itemMana->Coll(player->Get_Get_Item());
	mapBombMana->Coll(shake_Counter.flg, con, player->Get_Switch_On());
	mapSwitch->Coll(player->Get_Switch_On());
	rockAttackMana->Coll();

	//�S�Ă̓����蔻�肪�I�������猋�ʂɉ����ăI�u�W�F�N�g�𐶐�

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
		dust->Draw(Vector2(), Vector2());
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_Pal);
		DrawTex(title_Pos, title, true);
		DrawTex(text_Play_Pos, text_Play_Tex, true);
		DrawTex(text_Exit_Pos, text_Exit_Tex, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		ui->ExitDraw();
		break;
	case PLAYINIT:
	case PLAYINIT2:
	case PLAY:
	case MAPSET:
		PlayDraw(sc, shake);
		break;
	case GAMECLEAR:
		PlayDraw(sc, shake);
		break;
	case ENDING:
		DrawGraph(0, 0, haikei, true);
		ui->ExitDraw();
		break;
	default:
		break;
	}

	if (game_end_set == 2 || game_end_set == 3 || title_Flg == 4)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawTex(cursor_Pos, cursor, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	Box(Vector2(), GetColor(0, 0, 0), drawScene, true, Vector2(), Vector2(), WIDTH, HEIGHT);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

bool Game::Enter()
{
	if (con->TrlggerBotton(con->A) || con->TrlggerBotton(con->X) || (key->KeyTrigger(KEY_INPUT_Z) || key->KeyTrigger(KEY_INPUT_RETURN)))
	{
		PlaySoundMem(ketteiSE, DX_PLAYTYPE_BACK, true);
		return true;
	}
	return false;
}





void Game::PlayDraw(const Vector2& sc2, const Vector2& shake2)
{
	//Map�֘A
	backMap2->Draw(sc2, shake2);
	backMap->Draw(sc2, shake2);
	map->Draw(sc2, shake2);
	fuse->Draw(sc2, shake2);
	saveMana->Draw(sc2, shake2);
	itemMana->Draw(sc2, shake2);
	mapBombMana->Draw(sc2, shake2);
	mapSwitch->Draw(sc2, shake2);

	//�G�t�F�N�g�֘A1
	sideExMana->Draw(sc2, shake2);

	//�I�u�W�F�N�g�֘A
	enemy1Mana->Draw(sc2, shake2);
	enemy2->Draw(sc2, shake2);
	enemy3Mana->Draw(sc2, shake2);
	enemy4Mana->Draw(sc2, shake2);
	player->Draw(sc2, shake2);
	bombMana->Draw(sc2, shake2);
	sideBomb->Draw(sc2, shake2);
	rockAttackMana->Draw(sc2, shake2);

	//�G�t�F�N�g�֘A2
	exMana->Draw(sc2, shake2);
	dust->Draw(sc2, shake2);
	rockEffeMana->Draw(sc2, shake2);

	//UI�֘A
	ui->Draw(sc2, shake2);
}


