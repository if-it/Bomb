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
	ability = 0;
	up = false;
	down = false;
	left = false;
	right = false;
	ability_stop = Count();

	bomb_Vec = Vector2();
}


Player::~Player()
{
}

void Player::Init(std::vector<std::vector<int>>& map)
{
	game_object = GameObject("Player", true, Vector2(64.0f, 64.0f));
	ability1 = GameObject("Ability", false, Vector2(256.0f, 256.0f), Vector2());
	ability1.color = COLOR(120, 166, 58);

	ability1.SetPos(Vector2(game_object.GetPos().x - 128, game_object.GetPos().y - 128));

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
			}
		}
	}
	right = false;
	left = false;
	bomb_Spawn = false;
	blow = Count();
	now_Bomb_Num = max_Bomb_Num;
	ani = Animation();
	ability_stop = Count();

	invincible = Count();
}

void Player::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Player/PlayerDebug.png", MAXTEX, MAXTEX, 1, (int)game_object.game.texSize.x, (int)game_object.game.texSize.y, tex);
}

void Player::Input(Key* key, Controller* con, bool& time)
{

	up = false;
	down = false;
	right = false;
	left = false;
	bomb_Spawn = false;
	Vector2 stickL = con->StickL();
	if (key->KeyTrigger(KEY_INPUT_X) || con->TrlggerBotton(con->LB))
	{
		if (ability == 0)
		{
			ability = 1;
		}

	}
	if (key->KeyTrigger(KEY_INPUT_Z) || con->TrlggerBotton(con->RB))
	{
		if (ability == 0)
		{
			ability = 6;
		}
	}
	if (key->keyFlame(KEY_INPUT_UP) > 0 || key->keyFlame(KEY_INPUT_W) > 0 || stickL.y > 10000)
	{
		up = true;

		bomb_Vec = Vector2(0.0f, -1.0f);

	}
	if (key->keyFlame(KEY_INPUT_DOWN) > 0 || key->keyFlame(KEY_INPUT_S) > 0 || stickL.y < -10000)
	{
		down = true;
		bomb_Vec = Vector2(0.0f, 1.0f);
	}
	if (key->keyFlame(KEY_INPUT_D) > 0 || key->keyFlame(KEY_INPUT_RIGHT) > 0 || stickL.x > 10000)
	{
		right = true;
		game_object.game.lr = false;
		bomb_Vec = Vector2(1.0f, -0.2f);
	}
	if (key->keyFlame(KEY_INPUT_A) > 0 || key->keyFlame(KEY_INPUT_LEFT) > 0 || stickL.x < -10000)
	{
		left = true;
		game_object.game.lr = true;
		bomb_Vec = Vector2(-1.0f, -0.2f);
	}
	if (key->KeyTrigger(KEY_INPUT_SPACE) || con->TrlggerBotton(con->A))
	{
		bomb_Spawn = true;
	}
	bomb_Vec.Normalize();

	bomb_Vec = bomb_Vec * ABILITY_BOMB_SPEED;
	// time = ability;
	if (ability == 1 || ability == 3)ability1.game.dis = true;
	ability1.SetPos(Vector2(game_object.GetPos().x - 96, game_object.GetPos().y - 96));
}

void Player::Update(bool& shakeflg, BombMana* bomb)
{
	Move(shakeflg, bomb);

	ani.AnimationOn(GetRand(300), MAXTEX);
	invincible.Conuter(60);
	ability1.game.dis = ability;
	if (ability1.game.dis)
	{
		switch (ability)
		{
		case 0:
			break;
		case 1:
			ability1.game.scale.x += 0.05;
			ability1.game.scale.y += 0.05;
			if (ability1.game.scale >= Vector2(1.0f, 1.0f))
			{
				ability = 2;
				ability_stop.flg = true;
			}
			break;
		case 2:
			if (ability_stop.Conuter(10))
			{
				ability = 3;
				ability_stop = Count();
			}
			break;
		case 3:
			ability1.game.scale.x -= 0.05;
			ability1.game.scale.y -= 0.05;
			if (ability1.game.scale <= Vector2())
			{
				ability = 4;
				ability_stop.flg = true;
			}
			break;
		case 4:
			if (ability_stop.Conuter(1))
			{
				ability = 0;
				ability_stop = Count();
			}
			break;
		case 6:
			ability1.game.scale = Vector2(1.0f, 1.0f);
			ability_stop.flg = true;
			ability = 7;
			break;
		case 7:
			if (ability_stop.Conuter(30))
			{
				ability = 0;
				ability1.game.scale = Vector2();
			}
			break;
		default:
			break;
		}

	}
	ability1.game.dis = false;
	if ((ability >= 1 && ability <= 4) || (ability >= 6))ability1.game.dis = true;
	ability1.SetPos(Vector2(game_object.GetPos().x - 96, game_object.GetPos().y - 96));
	ability1.Size_Update();
}

void Player::Map_Coll_Update(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage)
{
	Map_Coll(collMap, sc, stageChange, stage);
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
	if (bomb_Spawn)
	{

		Vector2 bombPos = game_object.game.allVec.pos;
		bombPos += SIZE / 2;
		Vector2 bombVec = Vector2();

		if (now_Bomb_Num > 0)
		{
			bomb->BombSpawn(bombPos, bombVec, true, damage);
		}
	}
}



bool Player::Die()
{
	if (hp <= 0)return true;

	return false;
}

void Player::Map_Coll(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage)
{
	for (int i = 0; i < 5; ++i)
	{
		back_flg[i] = false;
		collFlg[i] = false;
	}
	vec = game_object.game.allVec.vec;

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

	sc = Vector2::Lerp(sc, sc2, 0.05f);
}

void Player::MapJub(const int& mapPoint, const int& pointNum, bool& stageChange, int& stage)
{
	if (pointNum == 0) //Y軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[0] && vec.y == 0)
			{
				back_flg[0] = true;
			}
		}
		if (WALL)
		{
			vec.y = 0;
			collFlg[0] = true;
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[1] && vec.y == 0)
			{
				back_flg[1] = true;
			}
		}
		if (WALL)
		{
			vec.y = 0;
			collFlg[1] = true;
		}
	}

	else if (pointNum == 2)//X軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[2] && vec.x == 0)
			{
				back_flg[2] = true;
			}
		}
		if (WALL)
		{
			vec.x = 0;
			collFlg[2] = true;
		}
	}

	else if (pointNum == 3)//X軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[3] && vec.x == 0)
			{
				back_flg[3] = true;
			}
		}
		if (WALL)
		{
			vec.x = 0;
			collFlg[3] = true;
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
			case 1:
				stage = 2;
				break;
			case 2:
				stage = 1;
				break;
			case 5:
				stage = 6;
				break;
			case 6:
				stage = 5;
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
			case 2:
				stage = 3;
				break;
			case 3:
				stage = 2;
				break;
			case 6:
				stage = 7;
				break;
			case 7:
				stage = 6;
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
			case 3:
				stage = 4;
				break;
			case 4:
				stage = 3;
				break;
			case 7:
				stage = 8;
				break;
			case 8:
				stage = 7;
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
			case 2:
				stage = 4;
				break;
			case 4:
				stage = 2;
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
			case 2:
				stage = 5;
				break;
			case 5:
				stage = 2;
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
		default:
			break;
		}
	}
}


void Player::Coll()
{
	float blowX = 0.0f;
	float blowY = 0.0f;
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "ex")
		{
			game_object.game.allVec.vec.y = 0;
			game_object.game.allVec.vec.y -= EXJUMP;
		}

		if (nameTag == "Enemy1")
		{
			blowX = 10.0f;
			blowY = 4.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr);
		}
		if (nameTag == "Enemy2")
		{
			blowX = 15.0f;
			blowY = 5.0f;
			Blow(blowX, blowY, game_object.coll_Obj_List[i]->lr);
		}

	}

}

void Player::Blow(const float& blowX, const float& blowY, const bool& lr)
{
	if (!invincible.flg)
	{
		invincible.flg = true;
		blow.flg = true;
		--hp;
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
	Circle(Vector2(ability1.GetPos().x + 128, ability1.GetPos().y + 128),
		ability1.GetSize().x / 2, 30, MyGetColor(ability1.color), ability1.game.dis, true, shake, sc);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaTex(game_object, tex[ani.num], true, shake, sc);
}