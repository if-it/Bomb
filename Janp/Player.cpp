#include "Player.h"


Player::Player()
{
	game_object = GameObject("Player", true, Vector2(64.0f, 64.0f));

	ability1 = GameObject("Ability", false, Vector2(128.0f, 128.0f));
	ability1.color = COLOR(0, 168, 108);
	max_Bomb_Num = 1;
	max_Hp = 3;
	hp = max_Hp;
	damage = 1;
	blow = Count();
	ability = false;
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
	ability1_flg = false;
	get_guide = false;
	switch_Coll = false;
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
		ability1_flg = save_Data.ability1_flg;
		sc2 = save_Data.sc;
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
	save_Data = { max_Hp,max_Bomb_Num,game_object.GetPos(),
		ability1_flg,sc2,save_Data.die_Count,save_Data.ability2_flg,save_Data.ability3_flg,save_Data.ability4_flg,save_Data.switch_On };
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
	max_Bomb_Num = 1;
	ability1_flg = false;
	save_Data.die_Count = 0;
	save_Data.ability2_flg = false;
	save_Data.ability3_flg = false;
	save_Data.ability4_flg = false;
	save_Data.switch_On = false;
}


//初期化
void Player::Init(std::vector<std::vector<int>>& map, Vector2& sc)
{
	game_object = GameObject("Player", true, Vector2(64.0f, 64.0f));


	move = false;
	ability1 = GameObject("Ability", false, Vector2(256.0f, 256.0f));
	ability1.color = COLOR(120, 166, 58);

	ability1.SetPos(Vector2(game_object.GetPos().x - 128, game_object.GetPos().y));

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

	animation = Animation();

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
	rota_Vec = 0;
	item_flg = 0;
	get_Item = 0;

	blinking = true;
	blinking_Count = Count();
	die_End = false;
}

void Player::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Player/Player.png", MAXTEX_X * MAXTEX_Y, MAXTEX_X, MAXTEX_Y,
		64, 64, player_Tex);
	load->LoadAnimeTex("Load/Texture/Player/Player_Black.png", MAXTEX_X * MAXTEX_Y, MAXTEX_X, MAXTEX_Y,
		64, 64, player_Black_Tex);
}

void Player::Input(Key* key, Controller* con, bool& time)
{

	up = false;
	down = false;
	right = false;
	left = false;
	bomb_Spawn = false;
	ability = false;
	get_guide = false;

	Vector2 stickL = con->StickL();
	if (ability1_flg && (key->keyFlame(KEY_INPUT_X) > 0 || con->FlameBotton(con->LB) > 0))
	{
		ability = true;
	}
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


		bomb_Vec = Vector2(1.0f, -0.2f);
	}
	if (key->keyFlame(KEY_INPUT_LEFT) > 0 || stickL.x < -10000)
	{
		left = true;
		game_object.game.lr = true;
		bomb_Vec = Vector2(-1.0f, -0.2f);
	}
	if (key->KeyTrigger(KEY_INPUT_SPACE) || con->TrlggerBotton(con->A))
	{
		bomb_Spawn = true;
	}
	if ((key->KeyTrigger(KEY_INPUT_Z) || con->TrlggerBotton(con->X)))
	{
		if (save_Coll)
		{
			save_On = true;
		}
		if (switch_Coll)
		{
			if (save_Data.switch_On)save_Data.switch_On = false;
			else save_Data.switch_On = true;
		}
		if (get_Item == 0 && (item_flg == 1 || item_flg == 2))
		{
			get_Item = 1;
		}
	}
	bomb_Vec.Normalize();

	bomb_Vec = bomb_Vec * ABILITY_BOMB_SPEED;
	time = ability;
	ability1.game.dis = ability;
	ability1.SetPos(Vector2(game_object.GetPos().x - 96, game_object.GetPos().y - 96));

}

void Player::Update(bool& shakeflg, BombMana* bomb)
{
	Move(shakeflg, bomb);
	invincible.Conuter(90);
	ability1.game.dis = ability;
	Animation_Update();
}

void Player::Map_Coll_Update(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage, bool& hetstop)
{
	Map_Coll(collMap, sc, stageChange, stage, hetstop);
	ability1.SetPos(Vector2(game_object.GetPos().x - 96, game_object.GetPos().y - 96));
	bomb_Vec = Vector2();
}



void Player::Move(bool& shakeflg, BombMana* bomb)
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
	if (blow.flg)game_object.game.allVec.vec = fVec;
	blow.Conuter(10);
	now_Bomb_Num = max_Bomb_Num - now_Bomb_Num;
	if (bomb_Spawn)//爆弾生成
	{

		Vector2 bombPos = game_object.GetPos();
		bombPos += SIZE / 2;
		Vector2 bombVec = Vector2();

		if (now_Bomb_Num > 0)
		{
			bomb->BombSpawn(bombPos, bombVec, true, damage);
		}
	}
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
	if (air)
	{
		animation.num = 0;
		one_move_flg = false;
		one_move_flg2 = false;
		one_stop_flg = false;
		animation.oneAnimeFlg = false;
		air_Back_Count = Count();
	}
	if (get_Item == 1)
	{
		get_Item = 2;
		if (item_flg == 1)
		{
			max_Hp++;
			hp++;
		}
		else if (item_flg == 2)
		{
			max_Bomb_Num++;
		}
	}

	if (save_Coll || item_flg > 0)
	{
		get_guide = true;
	}
}



bool Player::Die()
{
	if (hp <= 0)return true;

	return false;
}

void Player::Animation_Update()
{
	if (move)
	{
		one_stop_flg = false;
		animation_Count_Num = 10;
		animation.oneAnimeFlg = false;
		one_move_flg2 = false;
		animation.AnimationOn(animation_Count_Num, 12, 7);
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
	switch_Coll = false;

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
	sc = Vector2::Lerp(sc, sc2, 0.08f);
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
		if (mapPoint == 85)
		{
			switch_Coll = true;
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (mapPoint == 0 || TOGE)
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
		if (mapPoint == 3 || mapPoint == 50 || mapPoint == 58 || mapPoint == 59 || (mapPoint >= 66 && mapPoint <= 72))
		{
			bomb_Janp = false;
			game_object.game.rota = 0;
			rota_Vec = 0;
		}
		if (mapPoint == 90)
		{
			Space_On();
		}
		if (mapPoint == 85)
		{
			switch_Coll = true;
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
		if (mapPoint == 85)
		{
			switch_Coll = true;
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
		if (mapPoint == 85)
		{
			switch_Coll = true;
		}
	}
	else if (pointNum == 4)//中心
	{
		switch (mapPoint)
		{
		case 25:
			player_mapset = 35;
			stageChange = true;
			switch (stage)
			{
			case 301:
				stage = 302;
				break;
			case 302:
				stage = 301;
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
			case 200:
				stage = 302;
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
			default:
				break;
			}
			break;
		case 27:
			player_mapset = 37;
			stageChange = true;
			switch (stage)
			{

			default:
				break;
			}
			break;
		case 28:
			player_mapset = 38;
			stageChange = true;
			switch (stage)
			{

			default:
				break;
			}
			break;
		case 29:
			player_mapset = 39;
			stageChange = true;
			switch (stage)
			{

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
		case 85:
			switch_Coll = true;
			break;
		case 90:
			Space_On();
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

		if (nameTag == "Enemy1")
		{
			blowX = 10.0f;
			blowY = 4.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 1);
		}
		if (nameTag == "Enemy2")
		{
			blowX = 15.0f;
			blowY = 5.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 1);
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
	//Box(ability1, false, shake, sc);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	Circle(Vector2(ability1.GetPos().x + 128, ability1.GetPos().y + 128), 128, 30, MyGetColor(ability1.color), ability1.game.dis, true, shake, sc);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaTex(game_object, player_Tex[animation.num], true, shake, sc);
	if (!blinking)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawRotaTex(game_object, player_Black_Tex[animation.num], true, shake, sc);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}