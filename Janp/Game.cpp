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
	delete hpDropItemMana;

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
	title_Cursor = Vector2();
	title_Pos = Vector2(WIDTH / 2 - 384, HEIGHT / 2 - 192);
	text_Play_Pos = Vector2(WIDTH + 200, HEIGHT / 2 - 100);
	text_Option_Pos = Vector2(WIDTH + 200, HEIGHT / 2);
	text_Options_Pos = Vector2(WIDTH + 200, HEIGHT / 2);
	text_Exit_Pos = Vector2(WIDTH + 200, HEIGHT / 2 + 100);

	dust->TitleInit();

	load->LoadTex("Load/Texture/Title.png", title);
	load->LoadTex("Load/Texture/Text_Play.png", text_Play_Tex);

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
	hpDropItemMana->Init();

	shake = Vector2();
	sceneCount = Count();
	coll_List.clear();

	hetStop = Count();
	game_end_set = 0;
	cursor_Pos = Vector2();
	cursor_lerp = Vector2();
	game_end_on = false;
	reset_con = 0;

	option_Sound = false;
	option_Select = false;
	option_Controller = false;
	option_One_Shake = false;
	option_Sound_fle = 0.0f;
	play_option_Flg = 0;
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
	hpDropItemMana->Loading(load);

	load->LoadTex("Load/Texture/haikei.png", haikei);
	load->LoadTex("Load/Texture/Cursor.png", cursor);

	load->LoadTex("Load/Texture/Text_Exit.png", text_Exit_Tex);
	load->LoadTex("Load/Texture/Text_Option.png", text_Option_Tex);
	load->LoadTex("Load/Texture/Text_Back.png", text_Options_Tex[0]);
	load->LoadTex("Load/Texture/Text_Volume.png", text_Options_Tex[1]);
	load->LoadTex("Load/Texture/Text_Main.png", text_Options_Tex[2]);
	load->LoadTex("Load/Texture/Text_Music.png", text_Options_Tex[3]);
	load->LoadTex("Load/Texture/Text_Sound.png", text_Options_Tex[4]);
	load->LoadTex("Load/Texture/Text_Controller.png", text_Options_Tex[5]);
	load->LoadTex("Load/Texture/Text_Vibrotion.png", text_Options_Tex[6]);
	load->LoadTex("Load/Texture/Text_Title.png", text_Options_Tex[7]);

	load->LoadAnimeTex("Load/Texture/Text_On_Off.png", 2, 2, 1, 96, 48, text_On_Off);
	load->LoadAnimeTex("Load/Texture/Text_Num.png", 10, 10, 1, 19, 48, text_Num);

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
		option_Data = { 1.0f, 0.5f, 0.5f, false };
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
				PlaySoundMem(bgm1, DX_PLAYTYPE_LOOP, true);
				Bgm_Volume();
				Se_Volume();
				title_Flg = 1;
			}
			else
			{
				title_Flg = 0;
				scene = PLAYINIT;
				Data_Load();//デバック用
			}
		}
		break;
	case TITLE:
		if (game_end_set == 0)
		{
			if (title_Flg == 1 && SceneChangeSeb(8))//暗転タイトルまで
			{
				title_Flg = 0;
			}
			if (title_Flg == 0)//タイトル表示
			{
				title_Pal += 3;
				if (title_Pal >= 255)
				{
					title_Pal = 255;

					if (game_end_set == 0)
					{
						title_Flg = 2;//タイトル表示終わり
					}
				}
			}
			else if (title_Flg == 2)//タイトル左に移動
			{
				title_Pos = Vector2::Lerp(title_Pos, Vector2(50, HEIGHT / 2 - 192), 0.03f);
				if (title_Pos.x - 50 <= 5.0f)
				{
					title_Flg = 3;
				}
			}
			else if (title_Flg == 3)//テキスト表示
			{
				title_Pos = Vector2::Lerp(title_Pos, Vector2(50, HEIGHT / 2 - 192), 0.03f);
				text_Play_Pos = Vector2::Lerp(text_Play_Pos, Vector2(WIDTH - 500, HEIGHT / 2 - 100), 0.05f);
				if (text_Play_Pos.x - (WIDTH - 500) <= 100.0f)
				{
					text_Option_Pos = Vector2::Lerp(text_Option_Pos, Vector2(WIDTH - 469, HEIGHT / 2), 0.05f);
					if (text_Option_Pos.x - (WIDTH - 328) <= 10.0f)
					{
						text_Exit_Pos = Vector2::Lerp(text_Exit_Pos, Vector2(WIDTH - 500, HEIGHT / 2 + 100), 0.05f);
						if (text_Exit_Pos.x - (WIDTH - 500) <= 10.0f)
						{
							title_Flg = 4;
							cursor_Pos = Vector2(text_Play_Pos.x + 15, text_Play_Pos.y - 10);
							cursor_Pos2 = Vector2(cursor_Pos.x + 100, cursor_Pos.y);
							cursor_lerp = cursor_Pos;
							cursor_lerp2 = cursor_Pos2;
						}
					}
				}
			}
			else if (title_Flg == 4)//カーソル移動
			{
				text_Play_Pos = Vector2::Lerp(text_Play_Pos, Vector2(WIDTH - 500, HEIGHT / 2 - 100), 0.05f);
				text_Option_Pos = Vector2::Lerp(text_Option_Pos, Vector2(WIDTH - 469, HEIGHT / 2), 0.05f);
				text_Exit_Pos = Vector2::Lerp(text_Exit_Pos, Vector2(WIDTH - 500, HEIGHT / 2 + 100), 0.05f);

				Cursor(2, 0);

				if (title_Cursor.y == 0)
				{
					cursor_lerp = Vector2(text_Play_Pos.x + 15, text_Play_Pos.y - 10);
					cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
					if (Enter())title_Flg = 5;
				}
				else if (title_Cursor.y == 1)
				{
					cursor_lerp = Vector2(text_Option_Pos.x - 15, text_Option_Pos.y - 10);
					cursor_lerp2 = Vector2(cursor_lerp.x + 150, cursor_lerp.y);
					if (Enter())title_Flg = 7;
				}
				else if (title_Cursor.y == 2)
				{
					cursor_lerp = Vector2(text_Exit_Pos.x + 15, text_Exit_Pos.y - 10);
					cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
					if (Enter())game_end_set = 1;

				}
				if (key->keyFlame(KEY_INPUT_I) > 0 && key->keyFlame(KEY_INPUT_N) > 0 && key->keyFlame(KEY_INPUT_0) > 0)
				{
					Delete_Data();
				}
			}
			else if (title_Flg == 5)
			{
				title_Pos = Vector2::Lerp(title_Pos, Vector2(-1000, HEIGHT / 2 - 192), 0.03f);
				text_Option_Pos = Vector2::Lerp(text_Option_Pos, Vector2(WIDTH + 200, HEIGHT / 2), 0.05f);
				text_Exit_Pos = Vector2::Lerp(text_Exit_Pos, Vector2(WIDTH + 200, HEIGHT / 2 + 100), 0.05f);
				if (title_Pos.x < -800)
				{
					title_Flg = 6;
				}
			}
			else if (title_Flg == 7)//設定
			{
				title_Cursor = Vector2();
				text_Play_Pos = Vector2::Lerp(text_Play_Pos, Vector2(WIDTH + 200, HEIGHT / 2 - 100), 0.03f);

				text_Exit_Pos = Vector2::Lerp(text_Exit_Pos, Vector2(WIDTH + 200, HEIGHT / 2 + 100), 0.03f);
				if (text_Play_Pos.x > WIDTH + 100)
				{
					title_Flg = 8;
					option_Select = true;
				}
			}
			else if (title_Flg == 8)
			{
				text_Option_Pos = Vector2::Lerp(text_Option_Pos, Vector2(WIDTH - 469, HEIGHT / 2 - 200), 0.05f);
				text_Options_Pos = Vector2::Lerp(text_Options_Pos, Vector2(text_Option_Pos.x, HEIGHT / 2 - 100), 0.05f);
				cursor_lerp = Vector2(text_Option_Pos.x - 15, text_Option_Pos.y - 10);
				cursor_lerp2 = Vector2(cursor_lerp.x + 150, cursor_lerp.y);
				if (text_Option_Pos.y - (HEIGHT / 2 - 200) < 10.0f)
				{
					title_Flg = 9;

					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y - 10);
					cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
				}
			}
			else if (title_Flg == 9)//設定セレクト
			{
				text_Option_Pos = Vector2::Lerp(text_Option_Pos, Vector2(WIDTH - 469, HEIGHT / 2 - 200), 0.05f);
				text_Options_Pos = Vector2::Lerp(text_Options_Pos, Vector2(text_Option_Pos.x, HEIGHT / 2 - 100), 0.05f);

				Cursor(2, 0);

				if (title_Cursor.y == 0)
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y - 10);
					cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
					if (Enter())title_Flg = 10;
				}
				else if (title_Cursor.y == 1)
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 90);
					cursor_lerp2 = Vector2(cursor_lerp.x + 170, cursor_lerp.y);
					if (Enter())title_Flg = 11;
				}
				else if (title_Cursor.y == 2)
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 190);
					cursor_lerp2 = Vector2(cursor_lerp.x + 230, cursor_lerp.y);
					if (Enter())
					{
						title_Flg = 12;
						title_Cursor.x = (float)option_Data.con_shake;
					}
				}
				if (con->TrlggerBotton(con->B) || key->KeyTrigger(KEY_INPUT_ESCAPE) || con->TrlggerBotton(con->START))
				{
					title_Flg = 10;
				}
			}
			else if (title_Flg == 10)//戻る
			{
				text_Options_Pos = Vector2::Lerp(text_Options_Pos, Vector2(WIDTH + 200, HEIGHT / 2), 0.05f);
				text_Option_Pos = Vector2::Lerp(text_Option_Pos, Vector2(WIDTH - 469, HEIGHT / 2), 0.05f);
				cursor_lerp = Vector2(text_Option_Pos.x - 15, text_Option_Pos.y - 10);
				cursor_lerp2 = Vector2(cursor_lerp.x + 150, cursor_lerp.y);
				title_Cursor = Vector2();
				if (text_Options_Pos.x > WIDTH + 100)
				{
					title_Flg = 4;
				}
			}
			else if (title_Flg == 11)//音量
			{
				float cursor_Flg = 0.0f;
				option_Select = false;
				option_Sound = true;
				Cursor(3, 2);

				if (option_Sound_fle == 2 && title_Cursor.x == 0 ||
					option_Sound_fle == 0 && title_Cursor.x == 1 ||
					option_Sound_fle == 1 && title_Cursor.x == 2)
				{
					cursor_Flg = 0.1f;
				}
				if (option_Sound_fle == 0 && title_Cursor.x == 2 ||
					option_Sound_fle == 1 && title_Cursor.x == 0 ||
					option_Sound_fle == 2 && title_Cursor.x == 1)
				{
					cursor_Flg = -0.1f;
				}

				if (title_Cursor.y == 0)//back
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y - 10);
					cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
					if (Enter())
					{
						title_Flg = 9;
						option_Select = true;
						option_Sound = false;
						Option_Data_Save();
					}
				}
				else if (title_Cursor.y == 1)//main
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 90);
					cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);

					option_Data.Main_Volume += cursor_Flg;

					if (option_Data.Main_Volume > 1.01f)
					{
						option_Data.Main_Volume = 0.0f;
					}
					else if (option_Data.Main_Volume < 0.0f)
					{
						option_Data.Main_Volume = 1.0f;
					}

					Bgm_Volume();
					Se_Volume();
				}
				else if (title_Cursor.y == 2)//music
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 190);
					cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);
					option_Data.BGM_Volume += cursor_Flg;

					if (option_Data.BGM_Volume > 1.01f)
					{
						option_Data.BGM_Volume = 0.0f;
					}
					else if (option_Data.BGM_Volume < 0.0f)
					{
						option_Data.BGM_Volume = 1.0f;
					}

					Bgm_Volume();
				}
				else if (title_Cursor.y == 3)//sound
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 290);
					cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);
					option_Data.SE_Volume += cursor_Flg;

					if (option_Data.SE_Volume > 1.01f)
					{
						option_Data.SE_Volume = 0.0f;
					}
					else if (option_Data.SE_Volume < 0.0f)
					{
						option_Data.SE_Volume = 1.0f;
					}

					Se_Volume();
				}

				if (con->TrlggerBotton(con->B))
				{
					title_Flg = 9;
					option_Select = true;
					option_Sound = false;
					Option_Data_Save();
				}

				option_Sound_fle = title_Cursor.x;
			}
			else if (title_Flg == 12)//コントローラー
			{
				option_Select = false;
				option_Controller = true;

				Cursor(1, 1);

				if (title_Cursor.y == 0)
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y - 10);
					cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
					if (Enter())
					{
						title_Flg = 9;
						option_Select = true;
						option_Controller = false;
						Option_Data_Save();
					}
				}
				else if (title_Cursor.y == 1)
				{
					cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 90);
					cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);
					option_Data.con_shake = (bool)title_Cursor.x;
					con->Set_Shake_On(option_Data.con_shake);
					if (!option_One_Shake && option_Data.con_shake)
					{
						con->Shake(1000, 200);
					}
					option_One_Shake = (bool)title_Cursor.x;
				}

				if (GetJoypadNum() == 0)
				{
					++reset_con;
					if (reset_con == 180)
					{
						ReSetupJoypad();
						reset_con = 0;
					}
				}
				if (con->TrlggerBotton(con->B))
				{
					title_Flg = 9;
					option_Select = true;
					option_Controller = false;
					Option_Data_Save();
				}
			}



			if (title_Flg == 6 && !title_To_Play)//プレイシーンまで移動
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
				}
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
	case OPTION:
		if (play_option_Flg == 10)
		{
			scene = PLAY;
		}
		if (play_option_Flg == 1)
		{
			option_Select = true;
			text_Option_Pos = Vector2(WIDTH / 2 - 96, HEIGHT / 2 - 200);
			text_Options_Pos = Vector2(text_Option_Pos.x, HEIGHT / 2 - 100);

			Cursor(3, 0);

			if (title_Cursor.y == 0)
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y - 10);
				cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
				if (Enter())play_option_Flg = 10;
			}
			else if (title_Cursor.y == 1)
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 90);
				cursor_lerp2 = Vector2(cursor_lerp.x + 170, cursor_lerp.y);
				if (Enter())play_option_Flg = 2;
			}
			else if (title_Cursor.y == 2)
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 190);
				cursor_lerp2 = Vector2(cursor_lerp.x + 230, cursor_lerp.y);
				if (Enter())
				{
					play_option_Flg = 3;
					title_Cursor.x = (float)option_Data.con_shake;
				}
			}
			else if (title_Cursor.y == 3)
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 290);
				cursor_lerp2 = Vector2(cursor_lerp.x + 120, cursor_lerp.y);
				if (Enter())
				{
					title_Flg = 1;
				}
			}
			if (con->TrlggerBotton(con->B) || key->KeyTrigger(KEY_INPUT_ESCAPE) || con->TrlggerBotton(con->START))
			{
				play_option_Flg = 10;
			}
		}
		else if (play_option_Flg == 2)
		{
			float cursor_Flg = 0.0f;
			option_Select = false;
			option_Sound = true;
			Cursor(3, 2);

			if (option_Sound_fle == 2 && title_Cursor.x == 0 ||
				option_Sound_fle == 0 && title_Cursor.x == 1 ||
				option_Sound_fle == 1 && title_Cursor.x == 2)
			{
				cursor_Flg = 0.1f;
			}
			if (option_Sound_fle == 0 && title_Cursor.x == 2 ||
				option_Sound_fle == 1 && title_Cursor.x == 0 ||
				option_Sound_fle == 2 && title_Cursor.x == 1)
			{
				cursor_Flg = -0.1f;
			}

			if (title_Cursor.y == 0)//back
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y - 10);
				cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
				if (Enter())
				{
					play_option_Flg = 1;
					option_Select = true;
					option_Sound = false;
					Option_Data_Save();
				}
			}
			else if (title_Cursor.y == 1)//main
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 90);
				cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);

				option_Data.Main_Volume += cursor_Flg;

				if (option_Data.Main_Volume > 1.01f)
				{
					option_Data.Main_Volume = 0.0f;
				}
				else if (option_Data.Main_Volume < 0.0f)
				{
					option_Data.Main_Volume = 1.0f;
				}

				Bgm_Volume();
				Se_Volume();
			}
			else if (title_Cursor.y == 2)//music
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 190);
				cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);
				option_Data.BGM_Volume += cursor_Flg;

				if (option_Data.BGM_Volume > 1.01f)
				{
					option_Data.BGM_Volume = 0.0f;
				}
				else if (option_Data.BGM_Volume < 0.0f)
				{
					option_Data.BGM_Volume = 1.0f;
				}

				Bgm_Volume();
			}
			else if (title_Cursor.y == 3)//sound
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 290);
				cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);
				option_Data.SE_Volume += cursor_Flg;

				if (option_Data.SE_Volume > 1.01f)
				{
					option_Data.SE_Volume = 0.0f;
				}
				else if (option_Data.SE_Volume < 0.0f)
				{
					option_Data.SE_Volume = 1.0f;
				}

				Se_Volume();
			}
			if (con->TrlggerBotton(con->B) || key->KeyTrigger(KEY_INPUT_ESCAPE))
			{
				play_option_Flg = 1;
				option_Select = true;
				option_Sound = false;
				Option_Data_Save();
			}
			option_Sound_fle = title_Cursor.x;
		}
		else if (play_option_Flg == 3)
		{
			option_Select = false;
			option_Controller = true;

			Cursor(1, 1);

			if (title_Cursor.y == 0)
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y - 10);
				cursor_lerp2 = Vector2(cursor_lerp.x + 100, cursor_lerp.y);
				if (Enter())
				{
					play_option_Flg = 1;
					option_Select = true;
					option_Controller = false;
					Option_Data_Save();
				}
			}
			else if (title_Cursor.y == 1)
			{
				cursor_lerp = Vector2(text_Options_Pos.x - 15, text_Options_Pos.y + 90);
				cursor_lerp2 = Vector2(cursor_lerp.x + 400, cursor_lerp.y);
				option_Data.con_shake = (bool)title_Cursor.x;
				con->Set_Shake_On(option_Data.con_shake);
				if (!option_One_Shake && option_Data.con_shake)
				{
					con->Shake(1000, 200);
				}
				option_One_Shake = (bool)title_Cursor.x;
			}

			if (GetJoypadNum() == 0)
			{
				++reset_con;
				if (reset_con == 180)
				{
					ReSetupJoypad();
					reset_con = 0;
				}
			}
			if (con->TrlggerBotton(con->B) || key->KeyTrigger(KEY_INPUT_ESCAPE))
			{
				play_option_Flg = 1;
				option_Select = true;
				option_Controller = false;
				Option_Data_Save();
			}
		}
		break;
	case MENU:
		int num;
		num = 0;
		if (player->Get_Max_Bomb_Num() > 0)
		{
			num = 1;
		}
		if (player->Get_Ability1_Flg())
		{
			num = 2;
		}
		if (player->Get_Ability2_Flg())
		{
			num = 3;
		}
		if (player->Get_Ability3_Flg())
		{
			num = 4;
		}
		Cursor(0, num);
		ui->Menu(title_Cursor);
		if (key->KeyTrigger(KEY_INPUT_TAB) || con->TrlggerBotton(con->BACK)||con->TrlggerBotton(con->B))
		{
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
			scene = PLAY;
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
	if (game_end_set == 0 && (key->KeyTrigger(KEY_INPUT_ESCAPE) || con->TrlggerBotton(con->START)))
	{
		PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		if (scene == TITLE)
		{
			if (title_Flg != 1)game_end_set = 1;
		}
		else
		{
			scene = OPTION;
			play_option_Flg = 1;
		}
	}
	if (game_end_set == 2)
	{
		cursor_Pos = Vector2(743, 430);
		cursor_Pos2 = Vector2(849, 430);
		cursor_lerp = Vector2(743, 430);
		cursor_lerp2 = Vector2(849, 430);
		game_end_on = true;
		game_end_set = 3;
	}
	if (game_end_set == 3)
	{
		int stickLX = con->StickLTriggerX();
		if (key->KeyTrigger(KEY_INPUT_RIGHT) || stickLX == 1 || con->TrlggerBotton(con->RIGHT))
		{
			cursor_lerp = Vector2(743, 430);
			cursor_lerp2 = Vector2(849, 430);
			game_end_on = true;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}
		if (key->KeyTrigger(KEY_INPUT_LEFT) || stickLX == -1 || con->TrlggerBotton(con->LEFT))
		{
			cursor_lerp = Vector2(543, 430);
			cursor_lerp2 = Vector2(655, 430);
			game_end_on = false;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}
		if (Enter())
		{
			if (!game_end_on)game_end_flg = true;
			else game_end_set = 4;
		}
		if (con->TrlggerBotton(con->B) || key->KeyTrigger(KEY_INPUT_ESCAPE) || con->TrlggerBotton(con->START))
		{
			game_end_set = 4;
		}
	}
	cursor_Pos = Vector2::Lerp(cursor_Pos, cursor_lerp, 0.25f);
	cursor_Pos2 = Vector2::Lerp(cursor_Pos2, cursor_lerp2, 0.25f);

}

void Game::Data_Load()
{
	using namespace std;
	FILE* fp;

	std::string fileNama;
	fileNama = "Load/Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Meta/Meta_Data.dat";

	if (fopen_s(&fp, fileNama.c_str(), "rb") == 0)
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
	enemy2->Init(map->map, load, 255 * option_Data.SE_Volume * option_Data.Main_Volume);
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
	if (fopen_s(&fp, "Load/Data/SaveData/Option/Option_Data.dat", "wb") == 0)
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
	using namespace std;
	saveMana->Save_Mode();
	meta_Data.stage = stage;
	Option_Data_Save();
	std::string fileNama;
	fileNama = "Load/Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Meta/Meta_Data.dat";

	FILE* fp;
	if (fopen_s(&fp, fileNama.c_str(), "wb") == 0)
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

	enemy1Mana->Save();
	enemy3Mana->Save();
	enemy4Mana->Save();
}

void Game::Cursor(int numY, int numX)
{
	int stickLY = con->StickLTriggerY();
	int stickLX = con->StickLTriggerX();
	if (numY != 0)
	{
		if (key->KeyTrigger(KEY_INPUT_UP) > 0 || stickLY == 1 || con->TrlggerBotton(con->UP))
		{
			--title_Cursor.y;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}
		if (key->KeyTrigger(KEY_INPUT_DOWN) > 0 || stickLY == -1 || con->TrlggerBotton(con->DOWN))
		{
			++title_Cursor.y;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}

		if (title_Cursor.y < 0)
		{
			title_Cursor.y = numY;
		}
		if (title_Cursor.y > numY)
		{
			title_Cursor.y = 0;
		}
	}
	if (numX != 0)
	{
		if (key->KeyTrigger(KEY_INPUT_RIGHT) > 0 || stickLX == 1 || con->TrlggerBotton(con->RIGHT))
		{
			++title_Cursor.x;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}
		if (key->KeyTrigger(KEY_INPUT_LEFT) > 0 || stickLX == -1 || con->TrlggerBotton(con->LEFT))
		{
			--title_Cursor.x;
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		}

		if (title_Cursor.x < 0)
		{
			title_Cursor.x = numX;
		}
		if (title_Cursor.x > numX)
		{
			title_Cursor.x = 0;
		}
	}
}

void Game::Bgm_Volume()//BGM音量
{
	ChangeVolumeSoundMem(255 * option_Data.BGM_Volume * option_Data.Main_Volume, bgm1);
}

void Game::Se_Volume()//SE音量
{
	ChangeVolumeSoundMem(255 * option_Data.SE_Volume * option_Data.Main_Volume, selectSE);
	ChangeVolumeSoundMem(255 * option_Data.SE_Volume * option_Data.Main_Volume, ketteiSE);
	player->Se_Volume(255 * option_Data.SE_Volume * option_Data.Main_Volume);
	bombMana->Se_Volume(255 * option_Data.SE_Volume * option_Data.Main_Volume);
	exMana->Se_Volume(255 * option_Data.SE_Volume * option_Data.Main_Volume);
}

void Game::Play_Scene()
{
	flame_time = time;
	if (!player->Get_Save_On())
	{

		//Playerへの入力
		if (play_option_Flg == 10 && con->FlameBotton(con->A) == 0)
		{
			play_option_Flg = 0;
		}
		if (play_option_Flg == 0 && game_end_set == 0 && enemy2->Get_Ex_On() == 0)
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

				//layerチェック

				enemy1Mana->MoveChack(player->game_object.game.allVec.pos, coll);
				enemy4Mana->MoveChack(player->game_object.game.allVec.pos, coll);

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
	if (key->KeyTrigger(KEY_INPUT_TAB) || con->TrlggerBotton(con->BACK))
	{
		PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
		scene = MENU;
	}
}

void Game::Play_Scene_Update()
{
	map->Update();
	backMap2->Update(sc);

	player->Set_Now_Bomb_Num(bombMana->NowPlayerBombNum());
	player->Update(shake_Counter.flg, bombMana, sideBomb);
	enemy1Mana->Update(rockEffeMana, hpDropItemMana);
	enemy3Mana->Update(rockEffeMana, hpDropItemMana);
	enemy4Mana->Update(rockEffeMana, hpDropItemMana);
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
	hpDropItemMana->Update();

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
	//GameObjectリストの初期化
	coll_List.clear();
	//GameObjectリストにGameObjectの追加

	//player
	coll_List.push_back(&player->game_object);

	//アビリティ

	//SideBomb
	for (int i = 0; i < (int)sideExMana->sideEx.size(); ++i)
	{
		coll_List.push_back(&sideExMana->sideEx[i].game_object);
	}

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

	//HpDropItem

	for (int i = 0; i < (int)hpDropItemMana->hpDropItem.size(); ++i)
	{
		coll_List.push_back(&hpDropItemMana->hpDropItem[i].game_object);
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
	enemy3Mana->Coll(exMana->ex);
	enemy4Mana->Coll(exMana->ex);
	bombMana->Coll(shake_Counter.flg, con);
	enemy2->Coll(exMana->ex);
	saveMana->Coll();
	itemMana->Coll(player->Get_Get_Item());
	mapBombMana->Coll(shake_Counter.flg, con, player->Get_Switch_On());
	mapSwitch->Coll(player->Get_Switch_On());
	rockAttackMana->Coll();
	hpDropItemMana->Coll();

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
		dust->Draw(Vector2(), Vector2());
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_Pal);
		DrawTex(title_Pos, title, true);
		DrawTex(text_Play_Pos, text_Play_Tex, true);
		DrawTex(text_Exit_Pos, text_Exit_Tex, true);
		DrawTex(text_Option_Pos, text_Option_Tex, true);
		DrawTex(text_Options_Pos, text_Options_Tex[0], true);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 100), text_Options_Tex[1], option_Select);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 200), text_Options_Tex[5], option_Select);

		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 100), text_Options_Tex[2], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 200), text_Options_Tex[3], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 300), text_Options_Tex[4], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 100), text_Num[(int)option_Data.Main_Volume], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x + 270, text_Options_Pos.y + 100), text_Num[(int)(option_Data.Main_Volume * 10) % 10], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 200), text_Num[(int)option_Data.BGM_Volume], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x + 270, text_Options_Pos.y + 200), text_Num[(int)(option_Data.BGM_Volume * 10) % 10], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 300), text_Num[(int)option_Data.SE_Volume], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x + 270, text_Options_Pos.y + 300), text_Num[(int)(option_Data.SE_Volume * 10) % 10], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 100), text_Options_Tex[6], option_Controller);
		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 100), text_On_Off[(int)option_Data.con_shake], option_Controller);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		ui->ExitDraw();
		break;
	case PLAYINIT:
	case PLAYINIT2:
	case PLAY:
	case MAPSET:
		PlayDraw(sc, shake);
		break;
	case OPTION:
		PlayDraw(sc, shake);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
		Box(Vector2(), GetColor(0, 0, 0), true, true, Vector2(), Vector2(), WIDTH, HEIGHT);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawTex(text_Option_Pos, text_Option_Tex, true);
		DrawTex(text_Options_Pos, text_Options_Tex[0], true);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 100), text_Options_Tex[1], option_Select);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 200), text_Options_Tex[5], option_Select);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 300), text_Options_Tex[7], option_Select);

		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 100), text_Options_Tex[2], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 200), text_Options_Tex[3], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 300), text_Options_Tex[4], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 100), text_Num[(int)option_Data.Main_Volume], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x + 270, text_Options_Pos.y + 100), text_Num[(int)(option_Data.Main_Volume * 10) % 10], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 200), text_Num[(int)option_Data.BGM_Volume], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x + 270, text_Options_Pos.y + 200), text_Num[(int)(option_Data.BGM_Volume * 10) % 10], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 300), text_Num[(int)option_Data.SE_Volume], option_Sound);
		DrawTex(Vector2(text_Options_Pos.x + 270, text_Options_Pos.y + 300), text_Num[(int)(option_Data.SE_Volume * 10) % 10], option_Sound);

		DrawTex(Vector2(text_Options_Pos.x, text_Options_Pos.y + 100), text_Options_Tex[6], option_Controller);
		DrawTex(Vector2(text_Options_Pos.x + 250, text_Options_Pos.y + 100), text_On_Off[(int)option_Data.con_shake], option_Controller);


		break;
	case GAMECLEAR:
		PlayDraw(sc, shake);
		break;
	case ENDING:
		DrawGraph(0, 0, haikei, true);
		ui->ExitDraw();
		break;
	case MENU:
		PlayDraw(sc, shake);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
		Box(Vector2(), GetColor(0, 0, 0), true, true, Vector2(), Vector2(), WIDTH, HEIGHT);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		ui->MenuDraw();
		break;
	default:
		break;
	}

	if (game_end_set == 2 || game_end_set == 3 || title_Flg == 4 || title_Flg >= 7 || scene == OPTION)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawTex(cursor_Pos, cursor, true);
		DrawRotaTex(Vector2(cursor_Pos2.x + 16.0f, cursor_Pos2.y + 35.0f), Vector2(16.0f, 35.0f), Vector2(1.0f, 1.0f), 0.0f, cursor, true, true);
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
	//Map関連
	backMap2->Draw(sc2, shake2);
	backMap->Draw(sc2, shake2);
	map->Draw(sc2, shake2);
	fuse->Draw(sc2, shake2);
	saveMana->Draw(sc2, shake2);
	itemMana->Draw(sc2, shake2);
	mapBombMana->Draw(sc2, shake2);
	mapSwitch->Draw(sc2, shake2);

	//エフェクト関連1
	sideExMana->Draw(sc2, shake2);

	//オブジェクト関連
	enemy1Mana->Draw(sc2, shake2);
	enemy2->Draw(sc2, shake2);
	enemy3Mana->Draw(sc2, shake2);
	enemy4Mana->Draw(sc2, shake2);
	player->Draw(sc2, shake2);
	bombMana->Draw(sc2, shake2);
	sideBomb->Draw(sc2, shake2);
	rockAttackMana->Draw(sc2, shake2);
	hpDropItemMana->Draw(sc2, shake2);

	//手前Map関連
	map->FrontDraw(sc2, shake2);

	//エフェクト関連2
	exMana->Draw(sc2, shake2);
	dust->Draw(sc2, shake2);
	rockEffeMana->Draw(sc2, shake2);

	//UI関連
	ui->Draw(sc2, shake2);
}