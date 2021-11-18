#include "GameInclude.h"

GameInclude::GameInclude()
{
}

GameInclude::~GameInclude()
{
}

void GameInclude::ControllerOnly(bool on)
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



void GameInclude::Shake(Count& count, int num, Vector2 shakeMax, std::vector<std::vector<int>>& map)
{
	if (count.flg)
	{
		if (sc.x >= 0 && sc.x <= SIZE)
		{
			if (shakeMax.x > 0) 
			{ 
				shakeMax.x *= -1; 
			}
		}
		else if (sc.x <= map[0].size() * SIZE - WIDTH && sc.x >= map[0].size() * SIZE - WIDTH - SIZE)
		{
			if (shakeMax.x < 0)
			{
				shakeMax.x *= -1;
			}
		}
		if (sc.y == 0 && sc.y <= SIZE)
		{
			if (shakeMax.y > 0)shakeMax.y *= -1;
		}
		else if (sc.y <= map.size() * SIZE - HEIGHT && sc.y >= map.size() * SIZE - HEIGHT - SIZE)
		{
			if (shakeMax.y < 0)shakeMax.y *= -1;
		}

		shake = shakeMax;
	}
	else
	{
		shake = Vector2();
	}
	count.Conuter(num);
}