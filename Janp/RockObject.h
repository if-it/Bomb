#pragma once
#include "RockLightEffect.h"
#include"Load.h"
class RockObject :
	public Draw
{
public:
	RockObject();
	~RockObject();
	void Init(std::vector<std::vector<int>>& map);
	void Loading(int* tex);
	void Update();
	void Draw(const Vector2& sc, const Vector2& shake);
private:
	RockLightEffect rockLihgtEffect[5];
	int count;
	int* light_Tex;
	Animation light_Ani;
};

