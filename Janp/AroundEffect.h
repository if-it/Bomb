#pragma once
#include "Draw.h"
class AroundEffect :
    public Draw
{
public :
    AroundEffect();
    ~AroundEffect();
    void Init();
    void Update();
    void Draw(const int& tex);
    float rota;
    float subPal;
};

