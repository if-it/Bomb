#include "Save.h"

Save::Save()
{
	game_object = GameObject("Save",true,Vector2(128.0f, 64.0f));
}

Save::~Save()
{
}

void Save::Init(Vector2 pos)
{
	game_object.SetPos(pos);
	save_On_Mode = false;
	player_Coll = false;
}



void Save::Update()
{
}

void Save::Save_Mode()
{
	save_On_Mode = false;
	if (player_Coll)save_On_Mode = true;
}

void Save::Coll()
{
	player_Coll = false;
	for (int i = 0; i < (int)game_object.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = game_object.coll_Obj_List[i]->nameTag;
		if (nameTag == "Player")
		{
			player_Coll = true;
		}
	}
}

void Save::Draw(const Vector2& sc, const Vector2& shake, const int* tex)
{
	DrawTex(game_object, tex[(int)save_On_Mode], true, shake, sc);
}
