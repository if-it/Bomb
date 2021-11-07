#pragma once
#include "Bomb.h"
class OrbitBomb :
    public MapColl
{
public:
    OrbitBomb();
    ~OrbitBomb();
    void Init();
    void Loading(Load* load);
    void Update(const Vector2& pos,const Vector2& vec, std::vector<std::vector<int>>& collMap, const bool& dis);
    void Draw(const Vector2& sc, const Vector2& shake);

private:
    Bomb bomb;
    std::vector<GameObject> orbit;
    int count;
    int tex;
};

