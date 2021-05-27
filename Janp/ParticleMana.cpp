#include "ParticleMana.h"



ParticleMana::ParticleMana()
{
	for (int i = 0;i < PARTICLENUM;++i)
	{
		particle[i] = new Particle();
	}
}


ParticleMana::~ParticleMana()
{
	for (int i = 0;i < PARTICLENUM;++i)
	{
		delete particle[i];
	}
}

void ParticleMana::Init()
{
	for (int i = 0;i < PARTICLENUM;++i)
	{
		particle[i]->Init();
	}
	for (int y = 0;y < MAPY;++y)
	{
		for (int x = 0; x < MAPX;++x)
		{
			blockFlg[y][x] = false;
		}
	}
}


void ParticleMana::Update()
{
	for (int y = 0;y < MAPY;++y)
	{
		for (int x = 0; x < MAPX;++x)
		{
			if (blockFlg[y][x])
			{
				blockFlg[y][x] = false;
				int count = 0;
				for (int i = 0;i < PARTICLENUM;++i)
				{
					if (!particle[i]->par.dis)
					{
						particle[i]->Init(1, Vector2((float)(SIZE*x), (float)(SIZE*y)), boxTex);
						count++;
						if (count == 20)
						{
							break;
						}
					}
				}
			}
		}
	}
	for (int i = 0;i < PARTICLENUM;++i)
	{
		particle[i]->Update();
	}
}

void ParticleMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0;i < PARTICLENUM;++i)
	{

		particle[i]->Draw(sc, shake);
	}
}
