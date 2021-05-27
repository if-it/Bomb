#include "Particle.h"



Particle::Particle()
{

}


Particle::~Particle()
{
}



void Particle::Init(int num, const Vector2& pos, const int &texs)
{
	static const int POWER = 5;
	static const int ANG = 360;
	static const int PARSIZE = 3;
	type = num;
	tex = texs;
	vec = Vector2();
	size = Vector2(1.0f, 1.0f);
	switch (type)
	{
	case 0:
		par = GameObject(false);
		scale = 0;
		break;
	case 1:
		par = GameObject();
		par.allVec.pos = pos;
		par.allVec.vec = Vector2((float)(GetRand(POWER) - POWER / 2), (float)(-(GetRand(POWER) + 2)));
		par.allVec.ang.Normalize();
		par.pal = 255.0f;
		par.rote = (float)GetRand(90);
		scale = (float)(GetRand(PARSIZE) + 1);
		par.scale = Vector2(scale, scale);
		if (GetRand(1) == 1)
		{
			par.color = COLOR(66, 59, 59);
		}
		else
		{
			par.color = COLOR(99, 106, 111);
		}
		break;
	default:
		break;
	}
}

void Particle::Update()
{
	if (par.dis)
	{
		switch (type)
		{
		case 1:
			par.pal -= 3;
			par.allVec.vec.y += 0.1f;
			if (par.allVec.vec.x < 0)
			{
				par.allVec.vec.x += 0.01f;
			}
			else if (par.allVec.vec.x > 0)
			{
				par.allVec.vec.x -= 0.01f;
			}
			else
			{
				par.allVec.vec.x = 0.0f;
			}

			par.allVec.AddPos();
			break;
		default:
			break;
		}
		if (par.pal <= 0)
		{
			Init();
		}
	}
}

void Particle::Draw(const Vector2& sc, const Vector2& shake)
{
	if (par.dis)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)par.pal);
		SetBright(par.color);
		DrawRotaTex(par, tex, true, shake, sc, size, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetBright();
	}
}
