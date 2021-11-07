#pragma once
#include "BlockParticle.h"
class BlockParticleMana :
	public BlockParticle
{
public:
	BlockParticleMana();
	~BlockParticleMana();
	void Init();
	void Update(const int& stage);
	void Spawn(const Vector2& pos);
	int NowNum();
	void Draw(const Vector2& sc, const Vector2& shake);
private:
	std::vector<BlockParticle>block_Particle;
	int stage_Copy;
};

