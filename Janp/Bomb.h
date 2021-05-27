#pragma once
#include"Draw.h"
#define BSPEED 10.0f
#define EXJUMP 9.0f
class Bomb :public Draw
{
public:
	Bomb();
	~Bomb();
	void Init();
	void Update(bool &shakeflg, Controller * con);
	void Coll(Collision*coll, Vector2 pos, int size, Vector2&vec, bool &shakeflg, Controller * con);
	void Draw(const Vector2& sc, const Vector2& shake);
	int bombTex[8];
	int exTex[4];
	int exSound;
	struct BOMB
	{
		GameObject bomb;
		GameObject ex;
		ANIMATION bombAni;
		ANIMATION exAni;
		int time;
		bool exFlg;
		BOMB()
		{
			bomb = GameObject(false);
			ex = GameObject(false);
			bombAni = ANIMATION();
			exAni = ANIMATION();
			time = 0;
			exFlg = false;
		}
	};
	std::vector<BOMB> bomb;
private:

	void exSpawn(int i, bool &shakeflg);

	BOMB initBomb;
};

