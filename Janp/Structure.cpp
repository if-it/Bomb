#include "Structure.h"



Structure::Structure()
{
}


Structure::~Structure()
{
}



void Structure::SizeChange(Count& count, Vector2& size,  Vector2& sizeAdd, int maxCount, Vector2 change)
{
	if (count.flg)
	{
		sizeAdd += change;
		size += sizeAdd;
		if (count.Counter(maxCount))
		{
			size = Vector2(1.0f, 1.0f);
			sizeAdd = Vector2();
		}
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
