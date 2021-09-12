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
	ani = Animation();
}

void SideBomb::Loading(Load* load)
{
	load->LoadAnimeTex("Load/Texture/Bomb/SideBomb.png", 6, 6, 1, SIZE, SIZE, tex);
	load->LoadSound("Load/Sound/SE/shoot.wav", spawnSE);
}

void SideBomb::Update(Controller* con)
{
	if (live_Count.Conuter(200))
	{
		Init();
	}
	if (live_Count.count == 120)
	{
		game_object.game.allVec.vec = Vector2();
		explosion_on = true;
	}
	if (live_Count.count < 120)game_object.game.allVec.vec.y += 0.2f;
	if (explosion_on) ani.AnimationOn(1, 6);
}

void SideBomb::Map_Coll_Update(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}

void SideBomb::Spawn(const Vector2 set_pos)
{
	PlaySoundMem(spawnSE, DX_PLAYTYPE_BACK, true);
	game_object.game.dis = true;
	game_object.SetPos(Vector2((float)((int)((set_pos.x + 16.0f) / SIZE) * SIZE), (float)((int)((set_pos.y + 16.0f) / SIZE) * SIZE)));
	live_Count.flg = true;
}

void SideBomb::Draw(const Vector2& sc, const Vector2& shake)
{
	//Box(game_object, true, shake, sc);
	DrawRotaTex(game_object, tex[ani.num], true, shake, sc);
}