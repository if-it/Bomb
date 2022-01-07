#pragma once
#include "Draw.h"
#include"Load.h"
class OpeningScene :
    public Draw
{
public:
    OpeningScene();
    ~OpeningScene();
    void Init();
    void Loading(Load* load, int* tex,int*back);
    bool Update();
    void Draw();
    void Se_Volume(int volume);
    void Se_Sound();
private:
    int castle_Tex;
    int cloud_Tex;
    int* light_Tex;
    int* back_Tex;
    int kirameki_SE;

    int opening_Flg;
    int count;
    Vector2 castle_Pos;
    Vector2 cloud_Pos;
    Vector2 cloud_Pos2;
    Vector2 cloud_Pos3;
    Vector2 cloud_Pos4;
    Vector2 cloud_Vec;
    Vector2 light_Pos;
    Vector2 light_Vec;
    Animation light_Ani;
    Vector2 back_Pos;
};

