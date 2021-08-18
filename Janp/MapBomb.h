#pragma once
#include "Draw.h"
#include"ExplosionMana.h"
#include"Load.h"
class MapBomb :
    public Draw
{
public:
    MapBomb();
    ~MapBomb();
    void Init(std::vector<std::vector<int>>& map);
    void Loading(Load* load);
    void Update(bool& shakeflg, Controller* con, ExplosionMana* ex);
    void Draw(const Vector2& sc, const Vector2& shakeconst);
};

