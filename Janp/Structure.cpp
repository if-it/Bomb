#include "Structure.h"



Structure::Structure()
{
}


Structure::~Structure()
{
}



void Structure::SizeChange(Count & ani, Vector2&size, Vector2 change,int maxCount)
{
	if (ani.flg)
	{
		ani.count++;
		size.x += change.x;
		size.y += change.y;
	}
	if (ani.count == maxCount)
	{
		ani.count = 0;
		ani.flg = false;
		size = Vector2(1.0f,1.0f);
	}
}

void Structure::AnimeEnd(Count & ani, int maxCount, Vector2&size, Vector2 sizeNum)
{
	if (ani.count == maxCount)
	{
		ani.count = 0;
		ani.flg = false;
		size = sizeNum;
	}
}

void Structure::SetBright(COLOR color)
{
	SetDrawBright(color.red, color.green, color.blue);
}

unsigned int Structure::MyGetColor(COLOR color)
{
	return GetColor(color.red, color.green, color.blue);
}
