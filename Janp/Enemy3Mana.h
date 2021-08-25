#pragma once
#include "Enemy3.h"
#include"Load.h"
class Enemy3Mana:
    public Draw
{
public:
    Enemy3Mana();
    ~Enemy3Mana();
    void Init(std::vector<std::vector<int>>& collMap);
    void Loading(Load* load);
    void Update();
    void MapCollUpdate(std::vector<std::vector<int>>& collMap);
    void Coll(std::vector<Explosion>& ex);
    int NowNum();
    void Draw(const Vector2& sc, const Vector2& shake);
    std::vector<Enemy3> enemy3;
private:
    int enemy3Tex;
};

