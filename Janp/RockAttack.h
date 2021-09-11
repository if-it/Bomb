#pragma once
#include "Draw.h"
class RockAttack :
    public Draw
{
public:
    RockAttack();
    ~RockAttack();
    void Init(const Vector2 pos);
    void Update();
    void Coll();
    void Draw(const Vector2& sc, const Vector2& shake,const int& tex);
private:
    float rate;
};

