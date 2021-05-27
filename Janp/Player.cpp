#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Init(int(*map)[MAPX], Vector2 & sc)
{
	player = GameObject();
	player.color = COLOR(0, 0, 255);
	for (int y = 0;y < MAPY;++y)
	{
		for (int x = 0; x < MAPX;++x)
		{
			if (map[y][x] == mapNum)
			{
				player.allVec.pos = Vector2((float)(SIZE*x), (float)(SIZE*y));
				sc = Vector2(((float)(-WIDTH / 2) + SIZE * x), (float)((-HEIGHT / 2) + SIZE * y + SIZE / 2));
				if (player.allVec.pos.x < WIDTH / 2 - SIZE / 2)
				{
					sc.x = 0;
				}
				if (player.allVec.pos.x > (SIZE*MAPX) - WIDTH / 2 + SIZE / 2)
				{
					sc.x = (SIZE*MAPX) - WIDTH;
				}
				if (player.allVec.pos.y < HEIGHT / 2 + SIZE / 2)
				{
					sc.y = 0;
				}
				if (player.allVec.pos.y > (SIZE*MAPY) - HEIGHT / 2 - SIZE / 2)
				{
					sc.y = (SIZE*MAPY) - HEIGHT;
				}
			}
		}
	}
	right = false;
	left = false;
	jamp = false;
	jampFlg = false;
	exFlg = false;
	exPos = Vector2();
	ani = ANIMATION();
	exAnime = ANIMATION();
	jampAni = Count();

}

void Player::Update(Key * key, Controller * con, bool &shakeflg)
{
	Input(key, con);
	Move(shakeflg,con);
	ani.Animation(5, 8);
	if (exFlg)
	{
		if (exAnime.OneAnimation(5, 4))
		{
			exFlg = false;
		}
	}
	SizeChange(jampAni, player.scale, Vector2(-0.2f, 0.1f),5);
}

void Player::Input(Key * key, Controller * con)
{
	right = false;
	left = false;
	jamp = false;
	Vector2 stickL = con->StickL();
	if (key->keyFlame(KEY_INPUT_D) > 0 || key->keyFlame(KEY_INPUT_RIGHT) > 0 || stickL.x > 10000)
	{
		right = true;
		player.lr = false;
	}
	if (key->keyFlame(KEY_INPUT_A) > 0 || key->keyFlame(KEY_INPUT_LEFT) > 0 || stickL.x < -10000)
	{
		left = true;
		player.lr = true;
	}
	if (key->KeyTrigger(KEY_INPUT_SPACE)|| key->KeyTrigger(KEY_INPUT_UP) || key->KeyTrigger(KEY_INPUT_W) || con->TrlggerBotton(con->A))
	{
		jamp = true;
	}
}

void Player::Move(bool &shakeflg, Controller * con)
{
	player.allVec.vec.y += 0.2f;
	if (right)
	{
		player.allVec.vec.x += SPEED;
	}
	else if (left)
	{
		player.allVec.vec.x -= SPEED;
	}
	else if (player.allVec.vec.x > 0)
	{
		player.allVec.vec.x -= SPEED;
	}
	else if (player.allVec.vec.x < 0)
	{
		player.allVec.vec.x += SPEED;
	}
	if ((player.allVec.vec.x < 0 && player.allVec.vec.x>-SPEED) || (player.allVec.vec.x > 0 && player.allVec.vec.x < SPEED))
	{
		player.allVec.vec.x = 0;
	}


	if (player.allVec.vec.x > MAXSPEED)
	{
		player.allVec.vec.x = MAXSPEED;
	}
	if (player.allVec.vec.x < -MAXSPEED)
	{
		player.allVec.vec.x = -MAXSPEED;
	}

	if (jamp&&jampFlg)
	{
		con->Shake(1000, 250);
		jampFlg = false;
		player.allVec.vec.y -= JAMP;
		exPos = Vector2(player.allVec.pos.x, player.allVec.pos.y + SIZE / 2);
		exFlg = true;
		exAnime = ANIMATION();
		shakeflg = true;
		jampAni.flg = true;
		PlaySoundMem(exSound, DX_PLAYTYPE_BACK, true);
	}
}





void Player::Draw(const Vector2& sc, const Vector2& shake)
{
	//Box(player, true, shake, sc);
	DrawRotaTex(player, tex[ani.num], true, shake, sc);
	//Box(exPos, GetColor(255, 0, 0), exCount.flg, true, shake, sc);
	DrawTex(exPos, exTex[exAnime.num], exFlg, true, shake, sc);
}
