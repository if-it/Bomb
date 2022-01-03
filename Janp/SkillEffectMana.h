#pragma once
#include "SkillEffectOrigin.h"
#include"Load.h"
class SkillEffectMana :
	public SkillEffectOrigin
{
public:
	SkillEffectMana();
	~SkillEffectMana();
	void Init(const Vector2& pos);
	void Loading(int* itemtex, int& duat);
	void Update(const Vector2& sc);
	void Draw(const Vector2& sc, const Vector2& shake);

	bool Get_Skill_End() { return skill_End; }
private:
	int* tex;
	int lightTex;
	SkillEffectOrigin skill_Effect_Origin[8];
	Animation ani;
	bool skill_End;
};

