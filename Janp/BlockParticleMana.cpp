#include "BlockParticleMana.h"

BlockParticleMana::BlockParticleMana()
{
}

BlockParticleMana::~BlockParticleMana()
{
}

void BlockParticleMana::Init()
{
	block_Particle.clear();
	stage_Copy = 0;
}

void BlockParticleMana::Update(const int& stage)
{
	stage_Copy = stage;
	for (int i = 0; i < (int)block_Particle.size(); ++i)
	{
		block_Particle[i].Update();
	}
	if (NowNum() == 0)
	{
		block_Particle.clear();
	}
}

void BlockParticleMana::Spawn(const Vector2& pos)
{
	const int MAX_BLOCK = 8;
	for (int i = 0; i < MAX_BLOCK; ++i)
	{
		BlockParticle InitB;
		int size = GetRand(4) + 3;
		InitB.game_object = GameObject("", true, Vector2(size, size));
		InitB.game_object.SetPos(pos);
		InitB.game_object.game.allVec.vec = Vector2(GetRand(12) - GetRand(12),  -(GetRand(4)+3));
		if (stage_Copy >= 100 && stage_Copy < 200)
		{
			InitB.game_object.color = COLOR(29, 109, 146);
		}
		else if (stage_Copy >= 200 && stage_Copy < 300)
		{
			InitB.game_object.color = COLOR(88, 71, 60);

		}
		else if (stage_Copy >= 300 && stage_Copy < 400)
		{
			InitB.game_object.color = COLOR(119, 142, 155);
		}
		block_Particle.push_back(InitB);
	}
}

int BlockParticleMana::NowNum()
{
	int nowNum = 0;
	for (int i = 0; i < (int)block_Particle.size(); ++i)
	{
		if (block_Particle[i].game_object.game.dis)++nowNum;
	}
	return nowNum;
}

void BlockParticleMana::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)block_Particle.size(); ++i)
	{
		block_Particle[i].Draw(sc, shake);
	}
}
