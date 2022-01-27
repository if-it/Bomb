#include "OrbitBomb.h"

OrbitBomb::OrbitBomb()
{
	ani = Animation();
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
	load->LoadAnimeTex("Load/Texture/UI/Orbit.png",8,8,1,SIZE,SIZE,tex);
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

			bomb.Map_Coll_Update(collMap,1);

			if (count / 5 >=4&&(bomb.game_object.game.allVec.vec.x==0|| bomb.game_object.game.allVec.vec.y == 0)|| count / 5 >= 5)
			{
				orbit.push_back(bomb.game_object);
				break;
			}
			++count;
		}
		ani.AnimationOn(3, 8);
	}
}

void OrbitBomb::Draw(const Vector2& sc, const Vector2& shake)
{
	if (game_object.game.dis)
	{
		for (int i = 0; i < (int)orbit.size(); ++i)
		{
			DrawTex(orbit[i], tex[ani.num], true, shake, sc);
		}
	}
}
