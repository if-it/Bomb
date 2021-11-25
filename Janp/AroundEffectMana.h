#pragma once
#include "AroundEffect.h"
#include "Load.h"
#define AROUND_NUM 200
class AroundEffectMana :
	public AroundEffect
{
public:
	AroundEffectMana();
	~AroundEffectMana();
	void Init();
	void Spawen(const int& num, const int& hp);
	void Loading(Load* load);
	void Update(const int& hp);
	void Draw();
private:
	int tex;
	AroundEffect around_Efe[AROUND_NUM];
};

