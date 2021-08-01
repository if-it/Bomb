#pragma once
#include "Draw.h"
#include"Load.h"
class Save :
    public Draw
{
public:
    Save();
    ~Save();

    void Init(std::vector<std::vector<int>>& map);
    void Loading(Load* load);
    void Update();
    void Draw(const Vector2& sc, const Vector2& shake);
};

