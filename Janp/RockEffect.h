#pragma once
#include "Draw.h"
class RockEffect :
	public Draw
{
public:
	RockEffect();
	~RockEffect();
	void Init(const Vector2& pos);
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake, const int* tex);
private:
	float rota;
	int texNum;
};

