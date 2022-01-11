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

void Player::SaveData_Load(std::vector<std::vector<int>>& map, const int& data_Num, Vector2& sc)
{
	using namespace std;
	FILE* fp;

	string fileNama;

	fileNama = "Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Player/Player_Data.dat";

	if (fopen_s(&fp, fileNama.c_str(), "rb") == 0)
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
	using namespace std;
	hp = max_Hp;
	save_Data = { max_Hp,max_Bomb_Num,save_Data.damage,game_object.GetPos(),
		save_Data.ability1_flg,sc2,save_Data.die_Count,save_Data.ability2_flg,save_Data.ability3_flg,save_Data.ability4_flg,save_Data.switch_On };
	string fileNama;
	fileNama = "Data/SaveData/Data";
	fileNama += to_string(data_Num);
	fileNama += "/Player/Player_Data.dat";

	FILE* fp;
	if (fopen_s(&fp, fileNama.c_str(), "wb") == 0)
	{
		fwrite(&save_Data, sizeof(save_Data), 1, fp);
		fclose(fp);

		save_On = false;
	}
	else
	{
		MessageBox(NULL, "Player", "SaveData�̃G���[", MB_OK);
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


//������
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
				air_Pos = game_object.GetPos();
				sc2 = Vector2(((float)(-WIDTH / 2) + (SIZE * x + SIZE)), (float)((-HEIGHT / 2) + (SIZE * y + SIZE)));
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
	size_Change_Count = Count();
	size_Change_Count2 = Count();

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

	air_Sc = Vector2();
	ability2_Vec = Vector2();
	sideBomb_Vec = Vector2();
	size_Add = Vector2();
	size_Add2 = Vector2();
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
	exit_Ex = false;
	ex_Chain = 0.0f;
	junp_Chain = 0.0f;

}

void Player::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Player/Player.png", MAXTEX_X * MAXTEX_Y, MAXTEX_X, MAXTEX_Y,
		64, 64, player_Tex);
	load->LoadAnimeTex("Load/Texture/Player/Player_Black.png", MAXTEX_X * MAXTEX_Y, MAXTEX_X, MAXTEX_Y,
		64, 64, player_Black_Tex);
	load->LoadSound("Load/Sound/SE/Hit.wav", hitSE);
	load->LoadSound("Load/Sound/SE/Dash.wav", dashSE);
	load->LoadSound("Load/Sound/SE/walk.wav", walkSE);
	load->LoadSound("Load/Sound/SE/HpGet.wav", HpGetSE);
	load->LoadSound("Load/Sound/SE/kettei.wav", ketteiSE);
	load->LoadSound("Load/Sound/SE/Kanenone.wav", kanenoneSE);
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
		if (key->keyFlame(KEY_INPUT_UP) > 0 || stickL.y > 10000 || con->FlameBotton(con->UP))
		{
			up = true;

			bomb_Vec = Vector2(0.0f, -1.0f);

		}
		if (key->keyFlame(KEY_INPUT_DOWN) > 0 || stickL.y < -10000 || con->FlameBotton(con->DOWN))
		{
			down = true;
			bomb_Vec = Vector2(0.0f, 1.0f);
		}
		if (key->keyFlame(KEY_INPUT_RIGHT) > 0 || stickL.x > 10000 || con->FlameBotton(con->RIGHT))
		{
			right = true;



			bomb_Vec = Vector2(1.0f, -0.15f);
		}
		if (key->keyFlame(KEY_INPUT_LEFT) > 0 || stickL.x < -10000 || con->FlameBotton(con->LEFT))
		{
			left = true;

			bomb_Vec = Vector2(-1.0f, -0.15f);
		}
		if ((key->keyFlame(KEY_INPUT_SPACE) > 0 || con->FlameBotton(con->A) > 0))
		{
			bomb_Spawn = true;
		}
		if ((key->KeyTrigger(KEY_INPUT_Z) || con->TrlggerBotton(con->X)))
		{
			if (save_Coll)
			{
				save_On = true;
				PlaySoundMem(ketteiSE, DX_PLAYTYPE_BACK, true);
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
	invincible.Counter(90);
	bomb_Shot.Counter(30);
	Animation_Update();
}

void Player::Map_Coll_Update(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage, bool& hetstop)
{
	Map_Coll(collMap, sc, stageChange, stage, hetstop);
}



void Player::Move(bool& shakeflg, BombMana* bomb, SideBomb* sideBomb)
{
	//�ړ�
	game_object.game.allVec.vec.y += 0.2f;

	if (right)
	{
		game_object.game.allVec.vec.x += SPEED;
		game_object.game.lr = false;
	}
	else if (left)
	{
		game_object.game.allVec.vec.x -= SPEED;
		game_object.game.lr = true;
	}
	else if (game_object.game.allVec.vec.x > 0)//����
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
	//�ő�X�s�[�h
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

	if (bomb_Spawn)//���e����
	{
		if (!bomb_Shot.flg)Bomb_Spawn(bomb);
		bomb_Shot.flg = true;
	}

	//�_�b�V��
	if (ability2.Counter(15) || ability2_Activate == -1)
	{
		ability2_Activate = 0;
		ability2_Vec = Vector2();
		shadow_on = Count();
		ability2 = Count();
	}


	if (ability2_Activate == 1)
	{
		size_Change_Count2.flg = true;
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
		animation.num = 7;
		if (ability2_lr)
		{
			//��
			ability2_Vec.x += -ABILITY2_SPEED;
		}
		else
		{
			//�E
			ability2_Vec.x += ABILITY2_SPEED;
		}
		game_object.game.allVec.vec = ability2_Vec;

		if (shadow_on.Counter(2))
		{
			shadow_on.flg = true;
			shadow.push_back(game_object);
		}
	}
	ability2_on.Counter(25);

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


	//SideBomb����
	if (ability3_on == 1)
	{
		ability3_on = 2;
		size_Change_Count.flg = true;
		sideBomb->Spawn(game_object.GetPos());
	}
	if (!sideBomb->Get_live_Count_Flg())
	{
		ability3_on = 0;
	}

	//SideBomb����
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

	//�������
	if (blow.flg)
	{
		game_object.game.allVec.vec = fVec;
		size_Change_Count.flg = true;
	}
	blow.Counter(2);



	//�A�C�e����save�I�u�W�F�N�g
	if (save_Coll || item_flg > 0)
	{
		get_guide = 0;
	}

	if (get_Item == 1)
	{
		PlaySoundMem(ketteiSE, DX_PLAYTYPE_BACK, true);
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
		size_Change_Count.flg = true;
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
			animation.num = 6;
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
		animation.AnimationOn(animation_Count_Num, 12, 6);
		walk.flg = true;
		if (!air && walk.Counter(25))
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
	if (blinking_Count.Counter(9))
	{
		if (blinking)	blinking = false;
		else blinking = true;
	}
	SizeChange(size_Change_Count, game_object.game.scale, size_Add, 10, Vector2(-0.01f, 0.005f));
	SizeChange(size_Change_Count2, game_object.game.scale, size_Add2, 5, Vector2(0.0f, -0.05f));
}

//Map����
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
	through = false;

	int SizeCut = 0;

	//�㍶
	MapJub(MapPointerY(SizeCut + 1, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);
	//��E
	MapJub(MapPointerY(game_object.game.size.x - SizeCut - 1, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);
	//��^��
	MapJub(MapPointerY(game_object.game.size.x / 2, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);

	//����
	MapJub(MapPointerY(SizeCut + 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);
	//���E
	MapJub(MapPointerY(game_object.game.size.x - SizeCut - 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);
	//���^��
	MapJub(MapPointerY(game_object.game.size.x / 2, game_object.game.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);

	game_object.game.allVec.vec.y = vec.y;
	game_object.game.allVec.AddPosY();

	//�E��
	MapJub(MapPointerX(game_object.game.size.x - SizeCut - 1, SizeCut + 1, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);
	//�E��
	MapJub(MapPointerX(game_object.game.size.x - SizeCut - 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);
	//�E�^��
	MapJub(MapPointerX(game_object.game.size.x - SizeCut - 1, game_object.game.size.y / 2, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);

	//����
	MapJub(MapPointerX(SizeCut + 1, SizeCut + 1, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);
	//����
	MapJub(MapPointerX(SizeCut + 1, game_object.game.size.y - SizeCut - 1, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);
	//���^��
	MapJub(MapPointerX(SizeCut + 1, game_object.game.size.y / 2, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);

	//���S
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
	if (through)
	{
		collMap[byNum[4]][bxNum[4]] += 5;
		PlaySoundMem(kanenoneSE, DX_PLAYTYPE_BACK, true);
	}

	if (air_Array[0] && air_Array[1] && air_Array[2])
	{
		air = true;
	}

	if (!air)
	{
		ex_Chain = 0.0f;
		junp_Chain = 0.0f;
	}


	if (!air_Array[0] && !air_Array[1] && !air_Array[2])
	{
		air_Pos = game_object.GetPos();
		air_Sc = sc2;
	}

	float width = WIDTH / 2;
	float height = HEIGHT / 2;

	float scX = (game_object.GetPos().x + SIZE) / width;
	float scY = (game_object.GetPos().y + SIZE) / height;

	float mapMaxX = (SIZE * (int)collMap[0].size()) / width;
	float mapMaxY = (SIZE * (int)collMap.size()) / height;

	if (scX < 1)
	{
		sc2.x = 0;
	}
	else if (mapMaxX - 1 < scX)
	{
		sc2.x = (SIZE * (int)collMap[0].size()) - WIDTH;
	}
	else
	{
		sc2.x = game_object.GetPos().x + SIZE - width;
	}

	if (scY < 1)
	{
		sc2.y = 0;
	}
	else if (mapMaxY - 1 < scY)
	{
		sc2.y = (SIZE * (int)collMap.size()) - HEIGHT;
	}
	else
	{
		sc2.y = game_object.GetPos().y + SIZE - height;
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


//Map����
void Player::MapJub(const int& mapPoint, const int& pointNum, bool& stageChange, int& stage)
{
	if (pointNum == 0) //Y��
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
		if (NEEDLE)
		{
			toge_flg[0] = true;
		}
		if (mapPoint == 90)
		{
			Space_On();
		}
	}
	else if (pointNum == 1) //Y��
	{
		if (mapPoint == 0 || NEEDLE || mapPoint == 84)
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
		if (NEEDLE)
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

	else if (pointNum == 2)//X��
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
		if (NEEDLE)
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

	else if (pointNum == 3)//X��
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
		if (NEEDLE)
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
	else if (pointNum == 4)//���S
	{
		switch (mapPoint)
		{
		case 24:
			player_mapset = 34;
			stageChange = true;
			switch (stage)
			{
			
			default:
				break;
			}
			break;
		case 25:
			player_mapset = 35;
			stageChange = true;
			switch (stage)
			{
			case 200:
				stage = 301;
				break;
			case 301:
				stage = 200;
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
			case 300:
				stage = 301;
				break;
			case 301:
				stage = 300;
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
		case 90:
			Space_On();
			break;
		case 91:
			move_guide_on = true;
			break;
		case 200:
		case 201:
		case 202:
		case 203:
		case 204:
			through = true;
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
		//���S���o
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

void Player::Exit_Coll()
{
	//�������Ă�����Ԃ���O�ꂽ�Ƃ�
	for (int i = 0; i < (int)game_object.coll_Exit_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Exit_Obj_List[i]->nameTag;
		if (nameTag == "ex" || nameTag == "ex_player")
		{
			exit_Ex = false;
		}
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
			if (!exit_Ex)
			{
				++ex_Chain;
				if (ex_Chain > 5)
				{
					ex_Chain = 5;
				}

				if (ex_Chain == 1)
				{
					junp_Chain = EXJUMP;
				}
				else
				{
					junp_Chain = EXJUMP + ((float)ex_Chain / 3);
				}

				if (junp_Chain > EXJUMP * 2)
				{
					junp_Chain = EXJUMP * 2;
				}
				game_object.game.allVec.vec.y = 0;
				game_object.game.allVec.vec.y -= junp_Chain;
				bomb_Janp = true;
				rota_Vec = junp_Chain;
				size_Change_Count.flg = true;
				exit_Ex = true;
			}
		}
		else if (nameTag == "ex_player")
		{
			if (!exit_Ex)
			{
				game_object.game.allVec.vec.y = 0;
				game_object.game.allVec.vec.y -= EXJUMP;
				bomb_Janp = true;
				rota_Vec = EXJUMP;
				size_Change_Count.flg = true;
				exit_Ex = true;
			}
		}
		else if (nameTag == "RSideEx")
		{
			side_Ex_Coll = 1;
			rota_Vec = 10.0f;
		}
		else if (nameTag == "LSideEx")
		{
			side_Ex_Coll = 2;
			rota_Vec = 10.0f;
		}
		else if (nameTag == "Enemy1" || nameTag == "Enemy3")
		{
			blowX = 9.0f;
			blowY = 3.7f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 1);
		}
		else if (nameTag == "Enemy4")
		{
			blowX = 11.0f;
			blowY = 4.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 2);
		}
		else if (nameTag == "Enemy2")
		{
			blowX = 15.0f;
			blowY = 5.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 2);
		}
		else if (nameTag == "RockAttack")
		{
			blowX = 15.0f;
			blowY = 5.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr, hetstop, 1);
		}
		else if (nameTag == "Save")
		{
			save_Coll = true;
		}
		else if (nameTag == "Item1")
		{
			item_flg = 1;
		}
		else if (nameTag == "Item2")
		{
			item_flg = 2;
		}
		else if (nameTag == "Item3")
		{
			item_flg = 3;
		}
		else if (nameTag == "Item4")
		{
			item_flg = 4;
		}
		else if (nameTag == "Ability1")
		{
			item_flg = 5;
		}
		else if (nameTag == "Ability2")
		{
			item_flg = 6;
		}
		else if (nameTag == "Ability3")
		{
			item_flg = 7;
		}
		else if (nameTag == "HpDropItem")
		{
			++hp;
			PlaySoundMem(HpGetSE, DX_PLAYTYPE_BACK, true);
			if (hp > max_Hp)
			{
				hp = max_Hp;
			}
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

void Player::Se_Volume(int volume)
{
	ChangeVolumeSoundMem(volume, hitSE);
	ChangeVolumeSoundMem(volume, dashSE);
	ChangeVolumeSoundMem(volume, walkSE);
	ChangeVolumeSoundMem(volume, HpGetSE);
	ChangeVolumeSoundMem(volume, ketteiSE);
	ChangeVolumeSoundMem(volume, kanenoneSE);
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
	if (exit_Ex)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaTex(game_object, player_Black_Tex[animation.num], true, shake, sc);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (!blinking)
	{
		SetBright(COLOR(0, 0, 0));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawRotaTex(game_object, player_Black_Tex[animation.num], true, shake, sc);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetBright();
	}
}