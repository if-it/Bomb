#include "Explosion.h"


Explosion::Explosion()
{

}

Explosion::~Explosion()
{
}

void Explosion::Init()
{
	game_object = GameObject(false);
	exAni = ANIMATION();
}

void Explosion::Update()
{
	if (exAni.OneAnimation(10, 4))
	{
		game_object = GameObject(false);
	}
}

void Explosion::Map_Coll_Update(int(*collMap)[MAPX])
{
}

void Explosion::Coll(Collision* coll, ALLVECTOR all, Vector2 size, bool& shakeflg, Controller* con, const int& exSound)
{
}

void Explosion::Draw(const Vector2& sc, const Vector2& shake, const int* exTex)
{
	DrawRotaTex(game_object, exTex[exAni.num], true, shake, sc);
}
