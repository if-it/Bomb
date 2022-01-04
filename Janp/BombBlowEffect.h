#pragma once
#include "Draw.h"
class BombBlowEffect :
    public Draw
{
public:
    BombBlowEffect();
    ~BombBlowEffect();
    void Init(const Vector2&pos);
    void Update();
    void Draw(const Vector2& sc, const Vector2& shake,const int& tex);
};

