#pragma once
#include "Draw.h"
#define SPEED 0.2f
#define JAMP 5.5f
#define MAXSPEED 4
class Player :public Draw
{
public:
	Player();
	~Player();

	void Init(int(*map)[MAPX],Vector2 & sc);
	void Update(Key* key, Controller*con, bool &shakeflg);
	void Draw(const Vector2& sc, const Vector2& shake);

	int tex[8];
	int exTex[4];
	int exSound;
	GameObject player;
	Vector2 exPos;
	ANIMATION ani;
	ANIMATION exAnime;
	Count jampAni;
	bool exFlg;
	bool jampFlg;
	int mapNum;

private:
	void Input(Key* key, Controller*con);
	void Move(bool &shakeflg, Controller * con);


	bool left;
	bool right;
	bool jamp;
};

