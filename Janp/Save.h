#pragma once
#include "Draw.h"
#include"Load.h"
class Save :
    public Draw
{
public:
    Save();
    ~Save();

    void Init(Vector2 pos);
    void Update();
    void Save_Mode();
    void Coll();
    void Draw(const Vector2& sc, const Vector2& shake, const int* tex);

private:
    bool save_On_Mode;
    bool player_Coll;
};

