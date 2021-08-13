#pragma once
#include "Draw.h"
#include"Load.h"
#define MAP1 7
#define MAP2 12

class BackMap2 :
    public Draw
{
public:
    BackMap2();
    ~BackMap2();
    void Init(const int& stage, Load* load);
    void Loading(Load* load);
    void Update(const Vector2& sc);
    void Draw(const Vector2& sc, const Vector2& shake);
private:
    std::vector<std::vector<int>> backMap;
    int* tex;
    int stage2_Back_Tex[5];
    Vector2 back_Pos[5];
    Vector2 back_Pos2[5];
    Vector2 back_Sc[5];
    Vector2 back_Sc2[5];
    int back_count[5];
    int back_count2[5];
    int stage_S;
};

