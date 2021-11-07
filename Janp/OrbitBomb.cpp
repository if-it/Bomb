#include "OrbitBomb.h"

OrbitBomb::OrbitBomb()
{
}

OrbitBomb::~OrbitBomb()
{
}

void OrbitBomb::Init()
{
	game_object = GameObject();
	orbit.clear();
	bomb.Init();
	count = 0;
}

void OrbitBomb::Loading(Load* load)
{
	load->LoadTex("Load/Texture/UI/Orbit.png",tex);
}

void OrbitBomb::Update(const Vector2& pos, const Vector2& vec, std::vector<std::vector<int>>& collMap, const bool& dis)
{
	Init();
	game_object.game.dis = dis;
	bomb.game_object.game.dis = true;
	bomb.game_object.SetPos(pos + SIZE / 2);
	bomb.game_object.game.allVec.vec = vec;

	if (game_object.game.dis)
	{

		while (true)
		{
			bomb.game_object.game.allVec.vec.y += 0.1f;

			if (bomb.game_object.game.allVec.vec.x > 0)
			{
				bomb.game_object.game.allVec.vec.x -= 0.1f;
			}
			else if (bomb.game_object.game.allVec.vec.x < 0)
			{
				bomb.game_object.game.allVec.vec.x += 0.1f;
			}
			if ((bomb.game_object.game.allVec.vec.x < 0 && bomb.game_object.game.allVec.vec.x>-0.1f) ||
				(bomb.game_object.game.allVec.vec.x > 0 && bomb.game_object.game.allVec.vec.x < 0.1f))
			{
				bomb.game_object.game.allVec.vec.x = 0;
			}

			bomb.Map_Coll_Update(collMap);


			if (count % 5 == 0)
			{
				orbit.push_back(bomb.game_object);
			}
			if (count / 5 == 30||bomb.game_object.game.allVec.vec.x==0|| bomb.game_object.game.allVec.vec.y == 0)
			{
				break;
			}
			++count;
		}
	}
}

void OrbitBomb::Draw(const Vector2& sc, const Vector2& shake)
{
	if (game_object.game.dis)
	{
		for (int i = 0; i < (int)orbit.size(); ++i)
		{
			DrawTex(orbit[i], tex, true, shake, sc);
		}
	}
}
