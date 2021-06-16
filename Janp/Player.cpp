#include "Player.h"



Player::Player()
{
	game_object = GameObject(true, Vector2(64.0f, 64.0f));
	maxBombNum = 10;
}


Player::~Player()
{
}

void Player::Init(std::vector<std::vector<int>>& map)
{
	game_object = GameObject(true, Vector2(64.0f, 64.0f));
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] == player_mapset)
			{
				game_object.allVec.pos = Vector2((float)(SIZE * x), (float)(SIZE * y));
				sc2 = Vector2(((float)(-WIDTH / 2) + SIZE * x), (float)((-HEIGHT / 2) + SIZE * y + SIZE / 2));
				if (game_object.allVec.pos.x < WIDTH / 2 - SIZE / 2)
				{
					sc2.x = 0;
				}
				if (game_object.allVec.pos.x > (SIZE * (int)map[y].size()) - WIDTH / 2 + SIZE / 2)
				{
					sc2.x = (SIZE * (int)map[y].size()) - WIDTH;
				}
				if (game_object.allVec.pos.y < HEIGHT / 2 + SIZE / 2)
				{
					sc2.y = 0;
				}
				if (game_object.allVec.pos.y > (SIZE * (int)map.size()) - HEIGHT / 2 - SIZE / 2)
				{
					sc2.y = (SIZE * (int)map.size()) - HEIGHT;
				}
			}
		}
	}
	right = false;
	left = false;
	shot = false;
	nowBombNum = maxBombNum;
	ani = ANIMATION();
}

void Player::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/PlayerDebug.png", MAXTEX, MAXTEX, 1, (int)game_object.texSize.x, (int)game_object.texSize.y, tex);
}

void Player::Update(Key* key, Controller* con, bool& shakeflg, BombMana* bomb)
{
	Input(key, con);
	Move(shakeflg, con, bomb);

	ani.Animation(GetRand(300), MAXTEX);
}

void Player::Map_Coll_Update(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage)
{
	Map_Coll(collMap, sc, stageChange, stage);
}

void Player::Input(Key* key, Controller* con)
{
	right = false;
	left = false;
	shot = false;
	Vector2 stickL = con->StickL();
	if (key->keyFlame(KEY_INPUT_D) > 0 || key->keyFlame(KEY_INPUT_RIGHT) > 0 || stickL.x > 10000)
	{
		right = true;
		game_object.lr = false;
	}
	if (key->keyFlame(KEY_INPUT_A) > 0 || key->keyFlame(KEY_INPUT_LEFT) > 0 || stickL.x < -10000)
	{
		left = true;
		game_object.lr = true;
	}
	if (key->KeyTrigger(KEY_INPUT_SPACE) || key->KeyTrigger(KEY_INPUT_UP) || key->KeyTrigger(KEY_INPUT_W) || con->TrlggerBotton(con->A))
	{
		shot = true;
	}
}

void Player::Move(bool& shakeflg, Controller* con, BombMana* bomb)
{
	game_object.allVec.vec.y += 0.2f;
	if (right)
	{
		game_object.allVec.vec.x += SPEED;
	}
	else if (left)
	{
		game_object.allVec.vec.x -= SPEED;
	}
	else if (game_object.allVec.vec.x > 0)
	{
		game_object.allVec.vec.x -= SPEED;
	}
	else if (game_object.allVec.vec.x < 0)
	{
		game_object.allVec.vec.x += SPEED;
	}
	if ((game_object.allVec.vec.x < 0 && game_object.allVec.vec.x>-SPEED) || (game_object.allVec.vec.x > 0 && game_object.allVec.vec.x < SPEED))
	{
		game_object.allVec.vec.x = 0;
	}


	if (game_object.allVec.vec.x > MAXSPEED)
	{
		game_object.allVec.vec.x = MAXSPEED;
	}
	if (game_object.allVec.vec.x < -MAXSPEED)
	{
		game_object.allVec.vec.x = -MAXSPEED;
	}

	if (shot)
	{

		Vector2 bombPos = game_object.allVec.pos;
		bombPos += SIZE / 2;
		Vector2 bombVec = Vector2();
		nowBombNum = maxBombNum - nowBombNum;
		if (nowBombNum > 0)
		{
			bomb->BombSpawn(bombPos, bombVec, true);
		}
	}
}

void Player::Map_Coll(std::vector<std::vector<int>>& collMap, Vector2& sc, bool& stageChange, int& stage)
{
	for (int i = 0; i < 5; ++i)
	{
		back_flg[i] = false;
		collFlg[i] = false;
	}
	vec = game_object.allVec.vec;

	int SizeCut = 0;

	//上左
	MapJub(MapPointerY(SizeCut + 1, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);
	//上右
	MapJub(MapPointerY(game_object.size.x - SizeCut - 1, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);
	//上真ん中
	MapJub(MapPointerY(game_object.size.x / 2, SizeCut + 1, collMap, bxNum[0], byNum[0]), 0, stageChange, stage);

	//下左
	MapJub(MapPointerY(SizeCut + 1, game_object.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);
	//下右
	MapJub(MapPointerY(game_object.size.x - SizeCut - 1, game_object.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);
	//下真ん中
	MapJub(MapPointerY(game_object.size.x / 2, game_object.size.y - SizeCut - 1, collMap, bxNum[1], byNum[1]), 1, stageChange, stage);

	game_object.allVec.vec.y = vec.y;
	game_object.allVec.AddPosY();

	//右上
	MapJub(MapPointerX(game_object.size.x - SizeCut - 1, SizeCut + 1, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);
	//右下
	MapJub(MapPointerX(game_object.size.x - SizeCut - 1, game_object.size.y - SizeCut - 1, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);
	//右真ん中
	MapJub(MapPointerX(game_object.size.x - SizeCut - 1, game_object.size.y / 2, collMap, bxNum[2], byNum[2]), 2, stageChange, stage);

	//左上
	MapJub(MapPointerX(SizeCut + 1, SizeCut + 1, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);
	//左下
	MapJub(MapPointerX(SizeCut + 1, game_object.size.y - SizeCut - 1, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);
	//左真ん中
	MapJub(MapPointerX(SizeCut + 1, game_object.size.y / 2, collMap, bxNum[3], byNum[3]), 3, stageChange, stage);

	//中心
	MapJub(MapPointerX((game_object.size.x - SizeCut) / 2, (game_object.size.y - SizeCut) / 2, collMap, bxNum[4], byNum[4]), 4, stageChange, stage);

	game_object.allVec.vec.x = vec.x;
	game_object.allVec.AddPosX();

	for (int i = 0; i < 5; ++i)
	{
		if (back_flg[i])
		{
			collMap[byNum[i]][bxNum[i]] = 41;
		}
	}

	if (game_object.allVec.pos.x >= WIDTH / 2 - SIZE / 2 && game_object.allVec.pos.x <= (SIZE * (int)collMap[0].size()) - WIDTH / 2 )
	{
		sc2.x += vec.x;
	}

	if (game_object.allVec.pos.x < WIDTH / 2 - SIZE / 2)
	{
		sc2.x = 0;
	}
	if (game_object.allVec.pos.x > (SIZE * (int)collMap[0].size()) - WIDTH / 2)
	{
		sc2.x = (SIZE * (int)collMap[0].size()) - WIDTH;
	}


	if (game_object.allVec.pos.y >= HEIGHT / 2 + SIZE / 2 && game_object.allVec.pos.y <= (SIZE * (int)collMap.size()) - HEIGHT / 2 )
	{
		sc2.y += vec.y;
	}
	if (game_object.allVec.pos.y < HEIGHT / 2 )
	{
		sc2.y = 0;
	}
	if (game_object.allVec.pos.y > (SIZE * (int)collMap.size()) - HEIGHT / 2 )
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
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
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
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
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
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
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
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
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
		case 65:
			//clear = true;
			break;
		default:
			break;
		}
	}
}





void Player::Draw(const Vector2& sc, const Vector2& shake)
{
	DrawRotaTex(game_object, tex[ani.num], true, shake, sc);
}
