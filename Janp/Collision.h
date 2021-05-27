#pragma once
#include "Vector.h"
using Vector2 = vector::Vector2;
class Collision
{
public:
	Collision();
	~Collision();
	bool Collsion(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y);
	bool PointCollsion(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y);
	bool LineCollsionX(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y);
	bool LineCollsionY(Vector2 pos, int sizeY, int sizeX, Vector2 poss, int size2X, int size2Y);
};

