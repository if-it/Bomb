#pragma once
#include "Draw.h"
class BombSpawnEffect :
    public Draw
{
public:
    BombSpawnEffect();
    ~BombSpawnEffect();
    void Init();
    void Update(const Vector2&pos,const int&now_Bomb_Num);
    void Draw(const Vector2& sc, const Vector2& shake);

private:
    int fle_Bomb_Num;
    std::vector<GameObject> obj;
};

