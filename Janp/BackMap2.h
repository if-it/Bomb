#pragma once
#include "Draw.h"
#include"Load.h"
#define BACKMAP2_TEX_NUM 7

class BackMap2 :
    public Draw
{
public:
    BackMap2();
    ~BackMap2();
    void Init(const int& stage);
    void Loading(Load* load);
    void Update();
    void Draw(const Vector2& sc, const Vector2& shake);
private:
    std::vector<std::vector<int>> backMap;
    int tex[BACKMAP2_TEX_NUM];
};

