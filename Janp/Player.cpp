#include "Player.h"


Player::Player()
{
	game_object = GameObject("Player", true, Vector2(64.0f, 64.0f));

	max_Bomb_Num = 1;
	max_Hp = 3;
	hp = max_Hp;
	blow = Count();
	ability1_on = false;
	up = false;
	down = false;
	left = false;
	right = false;
	bomb_Janp = false;
	bomb_Vec = Vector2();
	air_Array[0] = false;
	air_Array[1] = false;
	air_Array[2] = false;
	air_Count = 0;
	air = false;
	rota_Vec = 0.0f;
	move = false;
	one_move_flg = false;

	animation_Count_Num = 10;
	one_stop_flg = false;
	save_Coll = false;
	save_On = false;
	space_On = false;
	get_guide = -1;
}


Player::~Player()
{
}

void Player::SaveData_Load(std::vector<std::vector<int>>& map, const int& date_Num, Vector2& sc)
{

	FILE* fp;

	std::string fileNama;
	switch (date_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Player/Player_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Player/Player_Data.dat";
		break;
	}
	if (fopen_s(&fp, fileNama.c_str(), "r") == 0)
	{
		fread_s(&save_Data, sizeof(save_Data), sizeof(save_Data), 1, fp);

		Init(map, sc);
		max_Hp = save_Data.max_Hp;
		max_Bomb_Num = save_Data.max_Bomb_Num;
		game_object.SetPos(save_Data.pos);
		sc2 = save_Data.sc;
		sc = sc2;
		fclose(fp);
	}
	else
	{
		Save_Data_Init(map, sc);
	}


	animation.num = 4;
	one_move_flg2 = true;
	move = false;

	hp = max_Hp;
	now_Bomb_Num = max_Bomb_Num;
}

void Player::Save(const int& data_Num)
{
	hp = max_Hp;
	save_Data = { max_Hp,max_Bomb_Num,save_Data.damage,game_object.GetPos(),
		save_Data.ability1_flg,sc2,save_Data.die_Count,save_Data.ability2_flg,save_Data.ability3_flg,save_Data.ability4_flg,save_Data.switch_On };
	std::string fileNama;
	switch (data_Num)
	{
	case 0:
		fileNama = "Load/Data/SaveData/Data01/Player/Player_Data.dat";
		break;
	default:
		fileNama = "Load/Data/SaveData/Data01/Player/Player_Data.dat";
		break;
	}

	FILE* fp;
	if (fopen_s(&fp, fileNama.c_str(), "w") == 0)
	{
		fwrite(&save_Data, sizeof(save_Data), 1, fp);
		fclose(fp);

		save_On = false;
	}
	else
	{
		MessageBox(NULL, "Player", "SaveDataのエラー", MB_OK);
		return;
	}
}

void Player::Save_Data_Init(std::vector<std::vector<int>>& map, Vector2& sc)
{
	player_mapset = 35;
	Init(map, sc);
	max_Hp = 3;
	max_Bomb_Num = 0;
	save_Data.ability1_flg = false;
	save_Data.damage = 2;
	save_Data.die_Count = 0;
	save_Data.ability2_flg = false;
	save_Data.ability3_flg = false;
	save_Data.ability4_flg = false;
	save_Data.switch_On = false;
}


//初期化
void Player::Init(std::vector<std::vector<int>>& map, Vector2& sc)
{
	bool lr_f = game_object.game.lr;
	game_object = GameObject("Player", true, Vector2(64.0f, 64.0f));
	game_object.game.lr = lr_f;

	move = false;


	fVec = Vector2();
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == player_mapset)
			{
				game_object.game.allVec.pos = Vector2((float)(SIZE * x), (float)(SIZE * y));
				sc2 = Vector2(((float)(-WIDTH / 2) + SIZE * x), (float)((-HEIGHT / 2) + SIZE * y + SIZE / 2));
				if (game_object.GetPos().x < WIDTH / 2 - SIZE / 2)
				{
					sc2.x = 0;
				}
				if (game_object.GetPos().x > (SIZE * (int)map[y].size()) - WIDTH / 2 + SIZE / 2)
				{
					sc2.x = (SIZE * (int)map[y].size()) - WIDTH;
				}
				if (game_object.GetPos().y < HEIGHT / 2 + SIZE / 2)
				{
					sc2.y = 0;
				}
				if (game_object.GetPos().y > (SIZE * (int)map.size()) - HEIGHT / 2 - SIZE / 2)
				{
					sc2.y = (SIZE * (int)map.size()) - HEIGHT;
				}
				sc = sc2;
			}
		}
	}

	right = false;
	left = false;
	bomb_Spawn = false;
	blow = Count();
	invincible = Count();
	air_Back_Count = Count();
	bomb_Shot = Count();
	animation = Animation();
	ability2 = Count();
	ability2_on = Count();
	walk = Count();

	for (int i = 0; i < 3; ++i)
	{
		air_Array[i] = false;
	}
	for (int i = 0; i < 5; ++i)
	{
		back_flg[i] = false;
		coll_flg[i] = false;
		toge_flg[i] = false;
	}
	air_Count = 0;
	air = false;
	one_stop_flg = 0;
	save_Coll = false;
	save_On = false;

	air_Pos = Vector2();
	air_Sc = Vector2();
	ability2_Vec = Vector2();
	sideBomb_Vec = Vector2();
	rota_Vec = 0;
	item_flg = 0;
	get_Item = 0;

	blinking = true;
	blinking_Count = Count();
	die_End = false;
	ground_ability2_on = false;
	ability2_Activate = 0;
	ability2_lr = false;
	shadow.clear();
	shadow_on = Count();
	ability3_on = 0;
	side_Ex_Coll = 0;
	tutorial_flg = 0;
	move_guide_on = false;
	get_guide = -1;

	control_flg = true;
}

void Player::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Player/Player.png", MAXTEX_X * MAXTEX_Y, MAXTEX_X, MAXTEX_Y,
		64, 64, player_Tex);
	load->LoadAnimeTex("Load/Texture/Player/Player_Black.png", MAXTEX_X * MAXTEX_Y, MAXTEX_X, MAXTEX_Y,
		64, 64, player_Black_Tex);
	load->LoadSound("Load/Sound/SE/Hit.wav", hitSE);
	ChangeVolumeSoundMem(180, hitSE);
	load->LoadSound("Load/Sound/SE/Dash.wav", dashSE);
	load->LoadSound("Load/Sound/SE/walk.wav", walkSE);
}

void Player::Input(Key* key, Controller* con, bool& time)
{
	up = false;
	down = false;
	right = false;
	left = false;
	bomb_Spawn = false;
	ability1_on = false;
	get_guide = -1;

	Vector2 stickL = con->StickL();
	if (control_flg)
	{
		if (key->keyFlame(KEY_INPUT_UP) > 0 || stickL.y > 10000)
		{
			up = true;

			bomb_Vec = Vector2(0.0f, -1.0f);

		}
		if (key->keyFlame(KEY_INPUT_DOWN) > 0 || stickL.y < -10000)
		{
			down = true;
			bomb_Vec = Vector2(0.0f, 1.0f);
		}
		if (key->keyFlame(KEY_INPUT_RIGHT) > 0 || stickL.x > 10000)
		{
			right = true;
			game_object.game.lr = false;


			bomb_Vec = Vector2(1.0f, -0.15f);
		}
		if (key->keyFlame(KEY_INPUT_LEFT) > 0 || stickL.x < -10000)
		{
			left = true;
			game_object.game.lr = true;
			bomb_Vec = Vector2(-1.0f, -0.15f);
		}
		if (key->keyFlame(KEY_INPUT_SPACE) > 0 || con->FlameBotton(con->A) > 0)
		{
			bomb_Spawn = true;
		}
		if ((key->KeyTrigger(KEY_INPUT_Z) || con->TrlggerBotton(con->X)))
		{
			if (save_Coll)
			{
				save_On = true;
			}
			if (get_Item == 0 && (item_flg > 0))
			{
				get_Item = 1;
			}
			if (tutorial_flg == 10)
			{
				tutorial_flg = -1;
			}
		}
		if (save_Data.ability2_flg && !ground_ability2_on && !ability2_on.flg && (key->KeyTrigger(KEY_INPUT_X) || con->TrlggerBotton(con->LB)))
		{
			ability2.flg = true;
			ground_ability2_on = true;
			ability2_Activate = 1;
		}
		if (save_Data.ability3_flg && ability3_on == 0 && (key->KeyTrigger(KEY_INPUT_C) || con->TrlggerBotton(con->B)))
		{
			ability3_on = 1;
		}
		if (tutorial_flg > 0)
		{
			time = true;
		}
		if (tutorial_flg == 0)
		{
			time = false;
		}
	}
}

void Player::Update(bool& shakeflg, BombMana* bomb, SideBomb* sideBomb)
{
	Move(shakeflg, bomb, sideBomb);
	invincible.Conuter(90);
	bomb_Shot.Conuter(30);
	Animation_Update();
}

void Player::Map_Coll_Update(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage, bool& hetstop)
{
	Map_Coll(collMap, sc, stageChange, stage, hetstop);
}



void Player::Move(bool& shakeflg, BombMana* bomb, SideBomb* sideBomb)
{
	//移動
	game_object.game.allVec.vec.y += 0.2f;

	if (right)
	{
		game_object.game.allVec.vec.x += SPEED;
	}
	else if (left)
	{
		game_object.game.allVec.vec.x -= SPEED;
	}
	else if (game_object.game.allVec.vec.x > 0)//制御
	{
		game_object.game.allVec.vec.x -= SPEED;
	}
	else if (game_object.game.allVec.vec.x < 0)
	{
		game_object.game.allVec.vec.x += SPEED;
	}
	if ((game_object.game.allVec.vec.x < 0 && game_object.game.allVec.vec.x>-SPEED) ||
		(game_object.game.allVec.vec.x > 0 && game_object.game.allVec.vec.x < SPEED))
	{
		game_object.game.allVec.vec.x = 0;
	}
	//最大スピード
	if (game_object.game.allVec.vec.x > MAXSPEED)
	{
		game_object.game.allVec.vec.x = MAXSPEED;
	}
	if (game_object.game.allVec.vec.x < -MAXSPEED)
	{
		game_object.game.allVec.vec.x = -MAXSPEED;
	}

	now_Bomb_Num = max_Bomb_Num - now_Bomb_Num;

	if (ability2.flg)
	{
		--now_Bomb_Num;
	}
	if (ability3_on > 0)
	{
		now_Bomb_Num -= 3;
	}
	if (now_Bomb_Num < 0)
	{
		if (ability2_Activate == 0)
		{
			ability3_on = 0;
		}
		if (ability2_Activate == 1)
		{
			ability2_Activate = -1;
		}
		if (ability2_Activate == 2)
		{
			if (ability3_on == 1)
			{
				ability3_on = 0;
			}
		}
	}
	if (now_Bomb_Num < 0)
	{
		now_Bomb_Num = 0;
	}

	if (save_Data.ability1_flg)
	{
		//ability1
		bomb_Vec.Normalize();

		bomb_Vec = bomb_Vec * ABILITY_BOMB_SPEED;
	}
	else
	{
		bomb_Vec = Vector2();
	}

	if (bomb_Spawn)//爆弾生成
	{
		if (!bomb_Shot.flg)Bomb_Spawn(bomb);
		bomb_Shot.flg = true;
	}

	//ダッシュ
	if (ability2.Conuter(12) || ability2_Activate == -1)
	{
		ability2_Activate = 0;
		ability2_Vec = Vector2();
		shadow_on = Count();
		ability2 = Count();
	}


	if (ability2_Activate == 1)
	{
		PlaySoundMem(dashSE, DX_PLAYTYPE_BACK, true);
		ability2_on.flg = true;
		shadow_on.flg = true;
		ability2_Activate = 2;
		ability2_lr = game_object.game.lr;
		if (ability2_lr)
		{
			ability2_Vec.x = -8;
		}
		else
		{
			ability2_Vec.x = 8;
		}
	}

	if (ability2_Activate == 2)
	{
		const float ABILITY2_SPEED = 1.5f;
		game_object.game.rota = 0;
		rota_Vec = 0;
		animation.num = 0;
		if (ability2_lr)
		{
			//左
			ability2_Vec.x += -ABILITY2_SPEED;
		}
		else
		{
			//右
			ability2_Vec.x += ABILITY2_SPEED;
		}
		game_object.game.allVec.vec = ability2_Vec;

		if (shadow_on.Conuter(2))
		{
			shadow_on.flg = true;
			shadow.push_back(game_object);
		}
	}
	ability2_on.Conuter(25);

	int shadow_Num = 0;
	for (int i = 0; i < (int)shadow.size(); ++i)
	{
		if (shadow[i].game.dis)
		{
			shadow[i].game.pal -= 30.0f;
			if (shadow[i].game.pal <= 0)
			{
				shadow[i].game.dis = false;
			}
		}
		else
		{
			++shadow_Num;
		}
	}

	if (shadow_Num == (int)shadow.size())
	{
		shadow.clear();
	}


	//SideBomb生成
	if (ability3_on == 1)
	{
		ability3_on = 2;
		sideBomb->Spawn(game_object.GetPos());
	}
	if (!sideBomb->Get_live_Count_Flg())
	{
		ability3_on = 0;
	}

	//SideBomb判定
	if (side_Ex_Coll >= 1)
	{
		if (side_Ex_Coll == 1)
		{
			sideBomb_Vec.x += 0.5f;
		}
		else if (side_Ex_Coll == 2)
		{
			sideBomb_Vec.x -= 0.5f;
		}
		if (sideBomb_Vec.x >= SIDE_EX_MAX_SPEED)
		{
			sideBomb_Vec.x = SIDE_EX_MAX_SPEED;
		}
		else if (sideBomb_Vec.x <= -SIDE_EX_MAX_SPEED)
		{
			sideBomb_Vec.x = -SIDE_EX_MAX_SPEED;
		}
		game_object.game.allVec.vec = sideBomb_Vec;
	}
	else
	{
		sideBomb_Vec = Vector2();
	}

	//吹っ飛び
	if (blow.flg)game_object.game.allVec.vec = fVec;
	blow.Conuter(2);



	//アイテムとsaveオブジェクト
	if (save_Coll || item_flg > 0)
	{
		get_guide = 0;
	}

	if (get_Item == 1)
	{
		get_Item = 2;
		if (item_flg == 1)
		{
			max_Bomb_Num++;
		}
		else if (item_flg == 2)
		{
			++max_Hp;
			++hp;
		}
		else if (item_flg == 3)
		{
			++hp;
		}
		else if (item_flg == 4)
		{
			++save_Data.damage;
		}
		else if (item_flg == 5)
		{
			save_Data.ability1_flg = true;
			tutorial_flg = 1;
		}
		else if (item_flg == 6)
		{
			save_Data.ability2_flg = true;
			tutorial_flg = 2;
		}
		else if (item_flg == 7)
		{
			save_Data.ability3_flg = true;
			tutorial_flg = 3;
		}
		get_guide = item_flg;
	}


}

void Player::Bomb_Spawn(BombMana* bomb)
{
	Vector2 bombPos = game_object.GetPos();
	bombPos += SIZE / 2;

	if (now_Bomb_Num > 0)
	{
		bomb->BombSpawn(bombPos, bomb_Vec, true, save_Data.damage);
	}
}



bool Player::Die()
{
	if (hp <= 0)return true;

	return false;
}

void Player::Animation_Update()
{

	if (rota_Vec >= 0)
	{
		game_object.game.rota += rota_Vec;
	}
	rota_Vec -= 0.1f;
	if (game_object.game.allVec.vec.x != 0.0f)
	{
		move = true;
		if (!one_move_flg)
		{
			one_move_flg = true;
			animation.num = 7;
		}
	}
	else
	{
		move = false;
		if (!one_move_flg2)
		{
			one_move_flg2 = true;
			animation.num = 0;
		}
	}


	if (move)
	{
		one_stop_flg = false;
		animation_Count_Num = 10;
		animation.oneAnimeFlg = false;
		one_move_flg2 = false;
		animation.AnimationOn(animation_Count_Num, 12, 7);
		walk.flg = true;
		if (!air && walk.Conuter(25))
		{
			PlaySoundMem(walkSE, DX_PLAYTYPE_BACK, true);
		}

	}
	else
	{
		if (!one_stop_flg)
		{
			animation_Count_Num = 25;
			one_move_flg = false;
		}

		if (animation.OneAnimation(animation_Count_Num, 3))
		{
			if (!one_stop_flg)
			{
				one_stop_flg = true;
				animation_Count_Num = GetRand(250);
			}
			if (animation.num == 4)
			{
				animation_Count_Num = 5;
			}
			if (animation.num == 5)
			{
				animation_Count_Num = 3;
				one_stop_flg = false;
			}
			animation.AnimationOn(animation_Count_Num, 6, 3);
		}
	}

	if (air)
	{
		animation.num = 0;
		one_move_flg = false;
		one_move_flg2 = false;
		one_stop_flg = false;
		animation.oneAnimeFlg = false;
		air_Back_Count = Count();
	}

	if (invincible.flg)
	{
		blinking_Count.flg = true;
	}
	else
	{
		blinking = true;
	}
	if (blinking_Count.Conuter(9))
	{
		if (blinking)	blinking = false;
		else blinking = true;
	}

}

//Map判定
void Player::Map_Coll(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage, bool& hetstop)
{
	for (int i = 0; i < 5; ++i)
	{
		back_flg[i] = false;
		coll_flg[i] = false;
		toge_flg[i] = false;
	}
	for (int i = 0; i < 3; ++i)
	{
		air_Array[i] = false;
	}
	air = false;
	vec = game_object.game.allVec.vec;
	air_Count = 0;
	space_On = false;
	move_guide_on = false;

	int SizeCut = 0;

	//上左
	MapJub(MapPointerY(SizeCut + 1, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);
	//上右
	MapJub(MapPointerY(game_object.game.size.x - SizeCut - 1, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);
	//上真ん中
	MapJub(MapPointerY(game_object.game.size.x / 2, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);

	//下左
	MapJub(MapPointerY(SizeCut + 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);
	//下右
	MapJub(MapPointerY(game_object.game.size.x - SizeCut - 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);
	//下真ん中
	MapJub(MapPointerY(game_object.game.size.x / 2, game_object.game.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);

	game_object.game.allVec.vec.y = vec.y;
	game_object.game.allVec.AddPosY();

	//右上
	MapJub(MapPointerX(game_object.game.size.x - SizeCut - 1, SizeCut + 1, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);
	//右下
	MapJub(MapPointerX(game_object.game.size.x - SizeCut - 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);
	//右真ん中
	MapJub(MapPointerX(game_object.game.size.x - SizeCut - 1, game_object.game.size.y / 2, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);

	//左上
	MapJub(MapPointerX(SizeCut + 1, SizeCut + 1, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);
	//左下
	MapJub(MapPointerX(SizeCut + 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);
	//左真ん中
	MapJub(MapPointerX(SizeCut + 1, game_object.game.size.y / 2, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);

	//中心
	MapJub(MapPointerX((game_object.game.size.x - SizeCut) / 2, (game_object.game.size.y - SizeCut) / 2, collMap, bxNum[4], byNum[4]), 4, stageChange, stage);

	game_object.game.allVec.vec.x = vec.x;
	game_object.game.allVec.AddPosX();

	for (int i = 0; i < 5; ++i)
	{
		if (back_flg[i])
		{
			collMap[byNum[i]][bxNum[i]] = 41;
		}
	}

	if (air_Array[0] && air_Array[1] && air_Array[2])
	{
		air = true;
	}
	if (!air_Array[0] && !air_Array[1] && !air_Array[2])
	{
		air_Pos = game_object.GetPos();
		air_Sc = sc2;
	}



	if (game_object.game.allVec.pos.x >= WIDTH / 2 - SIZE / 2 && game_object.game.allVec.pos.x <= (SIZE * (int)collMap[0].size()) - WIDTH / 2)
	{
		sc2.x += vec.x;
	}

	if (game_object.game.allVec.pos.x < WIDTH / 2 - SIZE / 2)
	{
		sc2.x = 0;
	}
	if (game_object.game.allVec.pos.x > (SIZE * (int)collMap[0].size()) - WIDTH / 2)
	{
		sc2.x = (SIZE * (int)collMap[0].size()) - WIDTH;
	}


	if (game_object.game.allVec.pos.y >= HEIGHT / 2 + SIZE / 2 && game_object.game.allVec.pos.y <= (SIZE * (int)collMap.size()) - HEIGHT / 2)
	{
		sc2.y += vec.y;
	}
	if (game_object.game.allVec.pos.y < HEIGHT / 2)
	{
		sc2.y = 0;
	}
	if (game_object.game.allVec.pos.y > (SIZE * (int)collMap.size()) - HEIGHT / 2)
	{
		sc2.y = (SIZE * (int)collMap.size()) - HEIGHT;
	}

	for (int i = 0; i < 5; ++i)
	{
		if (toge_flg[i])
		{
			Spine(hetstop);
			break;
		}
	}
	sc = Vector2::Lerp(sc, sc2, 0.07f);
}


//Map処理
void Player::MapJub(const int& mapPoint, const int& pointNum, bool& stageChange, int& stage)
{
	if (pointNum == 0) //Y軸
	{
		if (mapPoint == 40)
		{
			if (!coll_flg[0] && vec.y == 0)
			{
				back_flg[0] = true;
			}
		}
		if (WALL)
		{
			vec.y = 0;
			coll_flg[0] = true;
		}
		if (TOGE)
		{
			toge_flg[0] = true;
		}
		if (mapPoint == 90)
		{
			Space_On();
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (mapPoint == 0 || TOGE || mapPoint == 84)
		{
			air_Array[air_Count] = true;
			air_Count++;
		}
		if (mapPoint == 40)
		{
			if (!coll_flg[1] && vec.y == 0)
			{
				back_flg[1] = true;
			}
		}
		if (WALL)
		{
			vec.y = 0;
			coll_flg[1] = true;
		}
		if (TOGE)
		{
			toge_flg[1] = true;
		}
		if (mapPoint == 3 || mapPoint == 50 || mapPoint == 58 || mapPoint == 59 ||
			(mapPoint >= 4 && mapPoint <= 23) || (mapPoint >= 54 && mapPoint <= 56) || (mapPoint >= 66 && mapPoint <= 72))
		{
			bomb_Janp = false;
			game_object.game.rota = 0;
			rota_Vec = 0;
			ground_ability2_on = false;

		}
		if (mapPoint == 90)
		{
			Space_On();
		}
		if (mapPoint == 91)
		{
			move_guide_on = true;
		}
	}

	else if (pointNum == 2)//X軸
	{
		if (mapPoint == 40)
		{
			if (!coll_flg[2] && vec.x == 0)
			{
				back_flg[2] = true;
			}
		}
		if (WALL)
		{
			vec.x = 0;
			coll_flg[2] = true;
		}
		if (TOGE)
		{
			toge_flg[2] = true;
		}
		if (mapPoint == 90)
		{
			Space_On();
		}
		if (mapPoint == 91)
		{
			move_guide_on = true;
		}
	}

	else if (pointNum == 3)//X軸
	{
		if (mapPoint == 40)
		{
			if (!coll_flg[3] && vec.x == 0)
			{
				back_flg[3] = true;
			}
		}
		if (WALL)
		{
			vec.x = 0;
			coll_flg[3] = true;
		}
		if (TOGE)
		{
			toge_flg[3] = true;
		}
		if (mapPoint == 90)
		{
			Space_On();
		}
		if (mapPoint == 91)
		{
			move_guide_on = true;
		}
	}
	else if (pointNum == 4)//中心
	{
		switch (mapPoint)
		{
		case 24:
			player_mapset = 34;
			stageChange = true;
			switch (stage)
			{
			case 203:
				stage = 204;
				break;
			case 204:
				stage = 203;
				break;
			case 205:
				stage = 303;
				break;
			case 303:
				stage = 205;
				break;
			default:
				break;
			}
			break;
		case 25:
			player_mapset = 35;
			stageChange = true;
			switch (stage)
			{
			case 100:
				stage = 103;
				break;
			case 103:
				stage = 100;
				break;
			case 200:
				stage = 201;
				break;
			case 201:
				stage = 200;
				break;
			case 202:
				stage = 203;
				break;
			case 203:
				stage = 202;
				break;
			case 205:
				stage = 303;
				break;
			case 206:
				stage = 304;
				break;
			case 301:
				stage = 302;
				break;
			case 302:
				stage = 301;
				break;
			case 303:
				stage = 205;
				break;
			case 304:
				stage = 206;
				break;
			default:
				break;
			}
			break;
		case 26:
			player_mapset = 36;
			stageChange = true;
			switch (stage)
			{
			case 100:
				stage = 101;
				break;
			case 101:
				stage = 100;
				break;
			case 102:
				stage = 104;
				break;
			case 104:
				stage = 102;
				break;
			case 200:
				stage = 302;
				break;
			case 201:
				stage = 205;
				break;
			case 202:
				stage = 203;
				break;
			case 203:
				stage = 202;
				break;
			case 205:
				stage = 201;
				break;
			case 300:
				stage = 301;
				break;
			case  301:
				stage = 300;
				break;
			case 302:
				stage = 200;
				break;
			case 304:
				stage = 305;
				break;
			case 305:
				stage = 304;
				break;
			default:
				break;
			}
			break;
		case 27:
			player_mapset = 37;
			stageChange = true;
			switch (stage)
			{
			case 101:
				stage = 102;
				break;
			case 102:
				stage = 101;
				break;
			case 200:
				stage = 201;
				break;
			case 201:
				stage = 200;
				break;
			case 205:
				stage = 305;
				break;
			case 300:
				stage = 303;
				break;
			case 301:
				stage = 305;
				break;
			case 302:
				stage = 304;
				break;
			case 303:
				stage = 300;
				break;
			case 305:
				stage = 301;
				break;
			default:
				break;
			}
			break;
		case 28:
			player_mapset = 38;
			stageChange = true;
			switch (stage)
			{
			case 102:
				stage = 104;
				break;
			case 104:
				stage = 102;
				break;
			case 200:
				stage = 206;
				break;
			case 201:
				stage = 202;
				break;
			case 202:
				stage = 201;
				break;
			case 206:
				stage = 200;
				break;
			case 300:
				stage = 303;
				break;
			case 303:
				stage = 300;
				break;
			default:
				break;
			}
			break;
		case 29:
			player_mapset = 39;
			stageChange = true;
			switch (stage)
			{
			case 100:
				stage = 205;
				break;
			case 103:
				stage = 303;
				break;
			case 201:
				stage = 202;
				break;
			case 202:
				stage = 201;
				break;
			case 205:
				stage = 100;
				break;
			case 300:
				stage = 301;
				break;
			case 301:
				stage = 300;
				break;
			case 303:
				stage = 103;
				break;
			default:
				break;
			}
			break;
		case 40:
			back_flg[4] = true;
			break;
		case 66:
			//clear = true;
			break;
		case 90:
			Space_On();
			break;
		case 91:
			move_guide_on = true;
			break;
		default:
			break;
		}
	}
}

void Player::Spine(bool& hetstop)
{
	if (!invincible.flg)
	{
		toge_flg[4] = true;
		invincible.flg = true;
		SubHp(1, hetstop);
	}
}

void Player::SubHp(int subHp, bool& hetstop)
{
	hp -= subHp;
	hetstop = true;
	if (Die())
	{
		//死亡演出
		die_End = true;
	}
}

void Player::Space_On()
{
	if (now_Bomb_Num > 0)
	{
		space_On = true;
	}
}


void Player::Coll(bool& hetstop)
{
	item_flg = 0;
	side_Ex_Coll = 0;
	save_Coll = false;
	float blowX = 0.0f;
	float blowY = 0.0f;
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "ex")
		{
			game_object.game.allVec.vec.y = 0;
			game_object.game.allVec.vec.y -= EXJUMP;
			bomb_Janp = true;
			rota_Vec = 10.0f;
		}
		if (nameTag == "RSideEx")
		{
			side_Ex_Coll = 1;
			rota_Vec = 10.0f;
		}
		if (nameTag == "LSideEx")
		{
			side_Ex_Coll = 2;
			rota_Vec = 10.0f;
		}
		if (nameTag == "Enemy1" || nameTag == "Enemy3")
		{
			blowX = 9.0f;
			blowY = 3.7f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 1);
		}
		if (nameTag == "Enemy4")
		{
			blowX = 11.0f;
			blowY = 4.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 2);
		}
		if (nameTag == "Enemy2" || nameTag == "RockAttack")
		{
			blowX = 15.0f;
			blowY = 5.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 2);
		}
		if (nameTag == "Save")
		{
			save_Coll = true;
		}
		if (nameTag == "Item1")
		{
			item_flg = 1;
		}
		if (nameTag == "Item2")
		{
			item_flg = 2;
		}
		if (nameTag == "Item3")
		{
			item_flg = 3;
		}
		if (nameTag == "Item4")
		{
			item_flg = 4;
		}
		if (nameTag == "Ability1")
		{
			item_flg = 5;
		}
		if (nameTag == "Ability2")
		{
			item_flg = 6;
		}
		if (nameTag == "Ability3")
		{
			item_flg = 7;
		}
	}

}

void Player::TogeInit()
{
	if (toge_flg[4] && !Die())
	{
		game_object.SetPos(air_Pos);
		game_object.game.allVec.vec = Vector2();
		sc2 = air_Sc;
		animation.num = 4;
		game_object.game.rota = 0;
		rota_Vec = 0;
		invincible = Count();
	}
}



void Player::Blow(const float& blowX, const float& blowY, const bool& lr, bool& hetstop, int subHp)
{
	if (!invincible.flg)
	{
		PlaySoundMem(hitSE, DX_PLAYTYPE_BACK, true);
		invincible.flg = true;
		blow.flg = true;
		SubHp(subHp, hetstop);
		if (!lr)
		{
			fVec = Vector2(blowX, -blowY);
		}
		else
		{
			fVec = Vector2(-blowX, -blowY);
		}
	}
}


void Player::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)shadow.size(); ++i)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, shadow[i].game.pal);
		DrawRotaTex(shadow[i], player_Tex[animation.num], true, shake, sc);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaTex(game_object, player_Tex[animation.num], true, shake, sc);
	if (!blinking)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawRotaTex(game_object, player_Black_Tex[animation.num], true, shake, sc);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}