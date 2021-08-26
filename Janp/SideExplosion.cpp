#include "SideExplosion.h"

SideExplosion::SideExplosion()
{
}

SideExplosion::~SideExplosion()
{
}

void SideExplosion::Init(const Vector2& set_pos, const std::string& NameTag)
{
	game_object = GameObject(NameTag);
	game_object.SetPos(set_pos);
	game_object.game.scale.y = 0.1f;
	game_object.game.size = game_object.game.texSize * game_object.game.scale;
}

void SideExplosion::Update()
{
	game_object.game.scale.y += 0.1f;
	if (game_object.game.scale.y >= 1.0f)
	{
		game_object.game.scale.y = 1.0f;
	}
	game_object.game.size = game_object.game.texSize * game_object.game.scale;
}

bool SideExplosion::SizeSub()
{
	game_object.game.scale.y -= 0.2f;
	if (game_object.game.scale.y <= 0.0f)
	{
		game_object.game.scale.y = 0.0f;
		return true;
	}
	return false;
}


void SideExplosion::Draw(const Vector2& sc, const Vector2& shake, const int& tex)
{
	Box(game_object, true, shake, sc);
}
