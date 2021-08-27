#pragma once
#include "MapColl.h"
#include"Load.h"
#include"ExplosionMana.h"
class SideBomb :
    public MapColl
{
public:
    SideBomb();
    ~SideBomb();
    void Init();
    void Loading(Load* load);
    void Update(Controller* con);
    void Map_Coll_Update(std::vector<std::vector<int>>& collMap);
    void Spawn(const Vector2 set_pos);
    void Draw(const Vector2& sc, const Vector2& shake);

    bool& Get_Explosion_On() { return explosion_on; }
    bool& Get_live_Count_Flg() { return live_Count.flg; }
private:
    Count live_Count;
    bool explosion_on;
    int tex[6];
    Animation ani;
};

