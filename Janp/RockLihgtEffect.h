#pragma once
#include "Draw.h"
class RockLihgtEffect :
    public Draw
{
public:
    RockLihgtEffect();
    ~RockLihgtEffect();
    void Init(const Vector2&pos);
    void Update();
    void Draw(const Vector2& sc, const Vector2& shake);
private:
    float size_Vec;
};

