#include "GameInclude.h"

GameInclude::GameInclude()
{
}

GameInclude::~GameInclude()
{
}

void GameInclude::ControllerOn(bool on)
{
	controllerOnly = on;
}

int GameInclude::ConCheck()
{
	if (controllerOnly)return con->Set();

	return 0;
}
void GameInclude::ParentInit()
{
	loadCount = 0;
	pal = 255;
	drawScene = true;
	sceneChange = false;
	con->Init();
	key->Init();
}

bool GameInclude::SceneChangeSeb(int seb)
{
	pal -= seb;
	drawScene = true;
	if (pal <= 0)
	{
		pal = 0;
		//drawScene = false;
		return true;
	}
	return false;
}

bool GameInclude::SceneChangeAdd(int add)
{
	pal += add;
	drawScene = true;
	if (pal >= 255)
	{
		pal = 255;
		//drawScene = false;
		return true;
	}
	return false;
}

bool GameInclude::SceneChanger(int a)
{
	drawScene = true;
	if (!sceneChange)
	{
		if (SceneChangeAdd(a))
		{
			sceneChange = true;
		}
	}
	if (sceneChange)
	{
		if (SceneChangeSeb(a))
		{
			sceneChange = false;
			return true;
		}
	}
	return false;
}



void GameInclude::Shake(Count& count, int num, Vector2 shakeMax)
{
	if (count.flg)
	{
		shake = shakeMax;
	}
	else
	{
		shake = Vector2();
	}
	count.Conuter(num);
}