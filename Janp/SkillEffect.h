#pragma once
#include "Draw.h"
#include"Load.h"
class SkillEffect :
    public Draw
{
public:
    SkillEffect();
    ~SkillEffect();
    void Init(const Vector2& pos);
    void Update();
    void Draw(const Vector2& sc, const Vector2& shake,const int& tex);
private:
    bool sizeUp;
    Vector2 sizeVec;
};

