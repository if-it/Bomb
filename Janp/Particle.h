#pragma once
#include "Draw.h"
class Particle :public Draw
{
public:
	Particle();
	~Particle();
	int tex;
	void Init(int num = 0, const Vector2& pos = Vector2(), const int &texs = 0);
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
	GameObject par;
private:
	Vector2 vec;
	int type;
	float scale;
};

