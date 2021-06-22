#pragma once
#include"Enemy1.h"
#include"Load.h"
class Enemy1Mana :
    public MapColl
{
public:
    Enemy1Mana();
    ~Enemy1Mana();
    void Init(std::vector<std::vector<int>>& collMap);
    void Loading(Load* load);
    void Update();
    void MapCollUpdate(std::vector<std::vector<int>>& collMap);
    void MoveChack(const Vector2& pos, Collision* coll);
    void Coll(std::vector<Explosion>& ex);
    int NowNum();
    void Draw(const Vector2& sc, const Vector2& shake);
    std::vector<Enemy1> enemy1;
private:
    int enemy1Tex;
};

