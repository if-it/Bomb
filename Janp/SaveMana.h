#pragma once
#include "Draw.h"
#include"Load.h"
#include"Save.h"

class SaveMana :
	public Draw
{
public:
	SaveMana();
	~SaveMana();

	void Init(std::vector<std::vector<int>>& map);
	void Loading(Load* load);
	void Update();
	void Save_Mode();
	void Coll();
	void Draw(const Vector2& sc, const Vector2& shake);

	std::vector<Save> save;
private:
	int tex[2];
};

