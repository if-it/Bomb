#include "ParticleMana.h"



ParticleMana::ParticleMana()
{
	for (int i = 0; i < PARTICLENUM; ++i)
	{
		particle[i] = new Particle();
	}
}


ParticleMana::~ParticleMana()
{
	for (int i = 0; i < PARTICLENUM; ++i)
	{
		delete particle[i];
	}
}

void ParticleMana::Init()
{
	for (int i = 0; i < PARTICLENUM; ++i)
	{
		particle[i]->Init();
	}
}


void ParticleMana::Update()
{
	int count = 0;
	/*for (int i = 0; i < PARTICLENUM; ++i)
	{
		if (!particle[i]->par.dis)
		{
			particle[i]->Init(1, Vector2(), boxTex);
			count++;
			if (count == 20)
			{
				break;
			}
		}

	}*/
	for (int i = 0; i < PARTICLENUM; ++i)
	{
		particle[i]->Update();
	}
}

void ParticleMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < PARTICLENUM; ++i)
	{

		particle[i]->Draw(sc, shake);
	}
}
