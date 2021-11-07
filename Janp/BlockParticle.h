#pragma once
#include "Draw.h"
class BlockParticle :
	public Draw
{
public:
	BlockParticle();
	~BlockParticle();
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
};

