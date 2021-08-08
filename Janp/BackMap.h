#pragma once
#include "Draw.h"
#include"Load.h"
#define BACKMAP_TEX_NUM 13

class BackMap :
    public Draw
{
public:
    BackMap();
    ~BackMap();
    void Init(const int& stage);
    void Loading(Load* load);
    void Update();
    void Draw(const Vector2& sc, const Vector2& shake);
private:
    std::vector<std::vector<int>> backMap;
    int tex[BACKMAP_TEX_NUM];
};

