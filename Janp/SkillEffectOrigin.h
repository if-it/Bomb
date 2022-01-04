#pragma once
#include "SkillEffect.h"
#define SKILL_EFFECT_ORIGIN_SPEED 0.2f
class SkillEffectOrigin :
	public SkillEffect
{
public:
	SkillEffectOrigin();
	~SkillEffectOrigin();
	void Init(Vector2 ang, const Vector2& pos);
	void Update(const Vector2& sc);
	void Draw(const Vector2& sc, const Vector2& shake,const int& tex,const int& lightTex);
private:
	int count;

	SkillEffect skill_Effect[30];
};

