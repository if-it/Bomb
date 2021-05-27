#include "Mouse.h"



Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

void Mouse::Init()
{
	for (int i = 0;i < 3;++i)
	{
		botton[i] = false;
		flame[i] = 0;
	}
	wheelFlame = 0;
	wheelTriggr = false;
	x = 0;
	y = 0;
}

bool Mouse::TriggerMouseBotton(MouseBotton bot)
{
	if ((GetMouseInput() & bot) == 0)
	{
		botton[(int)bot] = false;
	}
	else if (!botton[(int)bot])
	{
		botton[(int)bot] = true;
		return true;
	}
	return false;
}

int Mouse::FlameMouseBotton(MouseBotton bot)
{
	if ((GetMouseInput() & bot) != 0)
	{
		flame[(int)bot]++;
		botton[(int)bot] = true;
	}
	else
	{
		flame[(int)bot] = 0;
		botton[(int)bot] = false;
	}
	return flame[(int)bot];
}

int Mouse::WheelTrigger()
{
	reWheel = GetMouseWheelRotVol();
	if (reWheel == 0)
	{
		wheelTriggr = false;
	}
	else if (reWheel >= 1 && !wheelTriggr)
	{
		wheelTriggr = true;
		return 1;
	}
	else if (reWheel <= -1 && !wheelTriggr)
	{
		wheelTriggr = true;
		return -1;
	}
	return 0;
}

int Mouse::WheelFleame()
{
	reWheel = GetMouseWheelRotVol();
	if (reWheel >= 1 || reWheel <= -1)
	{
		wheelTriggr = true;
	}
	else
	{
		wheelTriggr = false;
	}
	return GetMouseWheelRotVol();
}

vector::Vector2 Mouse::GetPoint()
{
	GetMousePoint(&x, &y);
	return Vector2(x, y);
}
