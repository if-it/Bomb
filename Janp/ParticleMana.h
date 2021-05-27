#pragma once
#include "Draw.h"
#include"Particle.h"
#define PARTICLENUM 500
class ParticleMana :public Draw
{
public:
	ParticleMana();
	~ParticleMana();
	void Init();
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
	int boxTex;
	Particle*particle[PARTICLENUM];
	bool blockFlg[MAPY][MAPX];
};

