#include "Draw.h"



Draw::Draw()
{
}


Draw::~Draw()
{
}

//éläpÇÃï`âÊ
void Draw::Box(Vector2 pos, unsigned int color, bool dis, bool flg, Vector2 shake, Vector2 sc, float sizeX, float sizeY)
{
	if (dis) DrawBoxAA(pos.x - sc.x + shake.x, pos.y - sc.y + shake.y,
		pos.x - sc.x + shake.x + sizeX + 1, pos.y - sc.y + shake.y + sizeY + 1, color, flg);
}

void Draw::Box(GameObject gameobject, bool flg, Vector2 shake, Vector2 sc)
{
	if (gameobject.game.dis) DrawBoxAA(gameobject.game.allVec.pos.x - sc.x + shake.x, gameobject.game.allVec.pos.y - sc.y + shake.y,
		gameobject.game.allVec.pos.x - sc.x + shake.x + gameobject.game.size.x, gameobject.game.allVec.pos.y - sc.y + shake.y + gameobject.game.size.y, MyGetColor(gameobject.color), flg);
}

void Draw::Circle(Vector2 pos, float r, int posnum, unsigned int color, bool dis, bool flg, Vector2 shake, Vector2 sc)
{
	//â~ÇÃï`âÊ
	if (dis)DrawCircleAA(pos.x - sc.x + shake.x, pos.y - sc.y + shake.y, r, posnum, color, flg);
}

void Draw::Circle(GameObject chara, float r, int posnum, bool flg, Vector2 shake, Vector2 sc)
{
	if (chara.game.dis)DrawCircleAA(chara.game.allVec.pos.x - sc.x + shake.x,
		chara.game.allVec.pos.y - sc.y + shake.y, r, posnum, MyGetColor(chara.color), flg);
}

//âÊëúÇÃí èÌï`âÊ
void Draw::DrawTex(Vector2 pos, int tex, bool dis, bool flg, const Vector2& shake, const Vector2& sc)
{
	if (dis)DrawGraphF(pos.x - sc.x + shake.x, pos.y - sc.y + shake.y, tex, flg);
}

void Draw::DrawTex(GameObject chara, int tex, bool flg, Vector2 shake, Vector2 sc)
{
	if (chara.game.dis)DrawGraphF(chara.game.allVec.pos.x - sc.x + shake.x, chara.game.allVec.pos.y - sc.y + shake.y, tex, flg);
}

void Draw::DrawUpTex(Vector2 pos, Vector2 size, int tex, bool dis, bool flg, Vector2 shake, Vector2 sc)
{
	//âÊëúÇÃägëÂèkè¨ï`âÊ
	if (dis)DrawExtendGraphF(pos.x - sc.x + shake.x, pos.y - sc.y + shake.y,
		pos.x + size.x + 1 - sc.x + shake.x, pos.y + size.y + 1 - sc.y + shake.y, tex, flg);
}

//âÊëúÇÃägëÂèkè¨ÅAâÒì]ÅAîΩì]ï`âÊ
void Draw::DrawRotaTex(Vector2 pos, Vector2 texPos, Vector2 up, float ang, int tex, bool dis, bool turn, bool flg, Vector2 shake, Vector2 sc)
{
	if (dis)DrawRotaGraph3F(pos.x - sc.x + shake.x, pos.y - sc.y + shake.y, texPos.x, texPos.y, up.x, up.y, PI / 180 * ang, tex, flg, turn);
}

void Draw::DrawRotaTex(const GameObject& chara, const int& tex, bool flg, const Vector2& shake, const Vector2& sc, bool center)
{
	if (!center)
	{
		if (chara.game.dis)DrawRotaGraph3F(chara.game.allVec.pos.x + chara.game.size.x / 2 - sc.x + shake.x,
			chara.game.allVec.pos.y + chara.game.size.y / 2 - sc.y + shake.y,
			chara.game.size.x / 2, chara.game.size.y / 2, chara.game.scale.x, chara.game.scale.y, PI / 180 * chara.game.rota, tex, flg, chara.game.lr);
	}
	else
	{
		if (chara.game.dis)DrawRotaGraph3F(chara.game.allVec.pos.x - sc.x + shake.x, chara.game.allVec.pos.y - sc.y + shake.y,
			chara.game.size.x / 2, chara.game.size.y / 2, chara.game.scale.x, chara.game.scale.y, PI / 180 * chara.game.rota, tex, flg, chara.game.lr);
	}

}
