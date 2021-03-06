#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}
//面
bool Collision::Collsion(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y)
{
	if (pos.x <= poss.x + size2X && poss.x <= pos.x + sizeX && pos.y <= poss.y + size2Y && poss.y <= pos.y + sizeY)
	{
		return true;
	}
	return false;
}
//GameObject版面
bool Collision::CollsionObj(const GameObject& gameobject1, const GameObject& gameobject2)
{
	if (gameobject1.game.dis && gameobject2.game.dis)
	{
		return Collsion(gameobject1.game.allVec.pos, gameobject1.game.size.x, gameobject1.game.size.y,
			gameobject2.game.allVec.pos, gameobject2.game.size.x, gameobject2.game.size.y);
	}
	return false;
}
//GameObject+Game
bool Collision::CollsionObj(const GameObject& gameobject1, const Game& gameobject2)
{
	if (gameobject1.game.dis && gameobject2.dis)
	{
		return Collsion(gameobject1.game.allVec.pos, gameobject1.game.size.x, gameobject1.game.size.y,
			gameobject2.allVec.pos, gameobject2.size.x, gameobject2.size.y);
	}
	return false;
}
//点と面
bool Collision::PointCollsion(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y)
{
	if (pos.x + sizeX <= poss.x + size2X && poss.x <= pos.x + sizeX && pos.y + sizeY <= poss.y + size2Y && poss.y <= pos.y + sizeY)
	{
		return true;
	}
	return false;
}
//線Xと面
bool Collision::LineCollsionX(Vector2 pos, int sizeX, int sizeY, Vector2 poss, int size2X, int size2Y)
{
	if (pos.x <= poss.x + size2X && poss.x <= pos.x + sizeX && pos.y + sizeY <= poss.y + size2Y && poss.y <= pos.y + sizeY)
	{
		return true;
	}
	return false;
}
//線Yと面
bool Collision::LineCollsionY(Vector2 pos, int sizeY, int sizeX, Vector2 poss, int size2X, int size2Y)
{
	if (pos.y <= poss.y + size2X && poss.y <= pos.y + sizeY && pos.x <= poss.x + size2Y && poss.x <= pos.x + sizeX)
	{
		return true;
	}
	return false;
}



