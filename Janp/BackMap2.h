#pragma once
#include "Draw.h"
#include"Load.h"
#define MAP1 7
#define MAP2 14
#define MAP2BACK 4
#define MAP3 22

class BackMap2 :
    public Draw
{
public:
    BackMap2();
    ~BackMap2();
    void Init(const int& stage, Load* load, const Vector2& sc);
    void Loading(Load* load);
    void Update(const Vector2& sc);
    void Draw(const Vector2& sc, const Vector2& shake);
    void Draw_Background(const Vector2& sc, const Vector2& shake);

    int stage_Back_Tex[MAP2BACK];
private:
    std::vector<std::vector<int>> backMap;
    int* tex;
    int texArray;
    Vector2 back_Pos[MAP2BACK];
    Vector2 back_Pos2[MAP2BACK];
    Vector2 back_Sc[MAP2BACK];
    Vector2 back_Sc2[MAP2BACK];
    int back_count[MAP2BACK];
    int back_count2[MAP2BACK];
    int stage_S;
    bool black;
};

