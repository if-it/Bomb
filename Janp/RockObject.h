#pragma once
#include "RockLihgtEffect.h"
#include"Load.h"
class RockObject :
	public Draw
{
public:
	RockObject();
	~RockObject();
	void Init(std::vector<std::vector<int>>& map);
	void Loading(Load* load);
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
private:
	RockLihgtEffect rockLihgtEffect[10];

};

