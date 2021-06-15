#pragma once
//#include<vector>
#include "Draw.h"
//using Vector2 = vector::Vector2;


class Collision :public Draw
{
public:
	Collision();
	~Collision();
	bool Collsion(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y);
	bool CollsionObj(const GameObject& gameobject1, const GameObject& gameobject2);
	bool PointCollsion(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y);
	bool LineCollsionX(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y);
	bool LineCollsionY(Vector2 pos, int sizeY, int sizeX, Vector2 poss, int size2X, int size2Y);
};

