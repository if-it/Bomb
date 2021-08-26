#include "SideBomb.h"

SideBomb::SideBomb()
{
}

SideBomb::~SideBomb()
{
}

void SideBomb::Init()
{
	game_object = GameObject("SideBomb", false);
	live_Count = Count();
	explosion_on = false;
}

void SideBomb::Loading(Load* load)
{
}

void SideBomb::Update(Controller* con)
{
	if (live_Count.Conuter(300))
	{
		Init();
	}
	if (live_Count.count == 120)
	{
		explosion_on = true;
	}
}

void SideBomb::Spawn(const Vector2 set_pos)
{
	game_object.game.dis = true;
	game_object.SetPos(Vector2((float)((int)((set_pos.x + 16.0f) / SIZE) * SIZE), (float)((int)((set_pos.y + 16.0f) / SIZE) * SIZE)));
	live_Count.flg = true;
}

void SideBomb::Draw(const Vector2& sc, const Vector2& shake)
{
	Box(game_object, true, shake, sc);
}