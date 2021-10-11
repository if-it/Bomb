#pragma once
#include "Draw.h"
class HpDropItem :
    public Draw
{
public:
    HpDropItem();
    ~HpDropItem();
    void Init();
    void Spawn(Vector2 pos);
    void Update();
    void Coll();
    void Draw(const Vector2& sc, const Vector2& shake, const int& HpTex);
private:
    int count;
};

