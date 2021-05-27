#include "Key.h"


Key::Key()
{
}


Key::~Key()
{
}

void Key::Init()
{
	for (int i = 0;i < 256;++i)
	{
		trigger[i] = false;
		flame[i] = 0;
	}
}

void Key::Input()
{
	GetHitKeyStateAll(key);
}

bool Key::KeyTrigger(int keyNum)
{
	if (key[keyNum] == 1 && !trigger[keyNum])
	{
		trigger[keyNum] = true;
		return true;
	}
	if (key[keyNum] != 1)
	{
		trigger[keyNum] = false;
	}
	return false;
}

int Key::keyFlame(int keyNum)
{
	if (key[keyNum] == 1)
	{
		flame[keyNum]++;
	}
	else
	{
		flame[keyNum] = 0;
	}
	return flame[keyNum];
}


