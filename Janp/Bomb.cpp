#include "Bomb.h"



Bomb::Bomb()
{
	for (int i = 0; i < 8; ++i)
	{
		bombTex[i] = 0;
	}
}


Bomb::~Bomb()
{
}

void Bomb::Init()
{
	bomb.clear();
	bomb.resize(20);
	for (int i = 0;i < (int)bomb.size();++i)
	{
		bomb[i] = BOMB();
	}
}

void Bomb::Update(bool &shakeflg, Controller * con)
{
	for (int i = 0;i < (int)bomb.size();++i)
	{
		if (bomb[i].bomb.dis)
		{
			bomb[i].bomb.allVec.vec.y += 0.1f;

			if (bomb[i].bomb.allVec.vec.x > 0)
			{
				bomb[i].bomb.allVec.vec.x -= 0.1f;
			}
			else if (bomb[i].bomb.allVec.vec.x < 0)
			{
				bomb[i].bomb.allVec.vec.x += 0.1f;
			}
			if ((bomb[i].bomb.allVec.vec.x < 0 && bomb[i].bomb.allVec.vec.x>-0.1f) ||
				(bomb[i].bomb.allVec.vec.x > 0 && bomb[i].bomb.allVec.vec.x < 0.1f))
			{
				bomb[i].bomb.allVec.vec.x = 0;
			}

			if (bomb[i].bombAni.OneAnimation(30, 8))
			{
				exSpawn(i,shakeflg);
				con->Shake(1000, 200);
			}
		}
		if (bomb[i].ex.dis)
		{
			if (bomb[i].exAni.OneAnimation(10, 4))
			{
				bomb[i].ex = GameObject(false);
			}
		}
	}
}

void Bomb::Coll(Collision * coll, Vector2 pos, int size, Vector2&vec, bool &shakeflg, Controller * con)
{
	for (int i = 0;i < (int)bomb.size();++i)
	{
		if (bomb[i].ex.dis)
		{
			if (!bomb[i].exFlg&&coll->Collsion(bomb[i].ex.allVec.pos, SIZE, SIZE, pos, size, size))
			{
				bomb[i].exFlg = true;
				
			}
		}
		if (bomb[i].bomb.dis)
		{
			if (coll->Collsion(bomb[i].bomb.allVec.pos, SIZE, SIZE, pos, size, size))
			{
				exSpawn(i,shakeflg);
				if (vec.y > 0) { vec.y = 0; }
				vec.y -= EXJUMP;
				con->Shake(1000, 300);
			}
		}

	}
}

void Bomb::exSpawn(int i,bool &shakeflg)
{
	bomb[i].ex.allVec.pos = bomb[i].bomb.allVec.pos;
	bomb[i].bomb.dis = false;
	bomb[i].ex.dis = true;
	bomb[i].exAni = ANIMATION();
	bomb[i].ex.allVec = bomb[i].bomb.allVec;
	shakeflg = true;
	PlaySoundMem(exSound, DX_PLAYTYPE_BACK, true);
}

void Bomb::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0;i < (int)bomb.size();++i)
	{
		DrawRotaTex(bomb[i].bomb, bombTex[bomb[i].bombAni.num], true, shake, sc);
		DrawRotaTex(bomb[i].ex, exTex[bomb[i].exAni.num], true, shake, sc);
	}
}


