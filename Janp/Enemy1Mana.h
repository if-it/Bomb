#pragma once
#include"Enemy1.h"
#include"Load.h"
using Die_Data = Enemy::Die_Data;

class Enemy1Mana :
    public MapColl
{
public:
    Enemy1Mana();
    ~Enemy1Mana();
    void Init(std::vector<std::vector<int>>& collMap, Load* load, const int& stage);
    void Save();
    void Update();
    void MapCollUpdate(std::vector<std::vector<int>>& collMap);
    void MoveChack(const Vector2& pos, Collision* coll);
    void Coll(std::vector<Explosion>& ex);
    int NowNum();
    void Draw(const Vector2& sc, const Vector2& shake);
    std::vector<Enemy1> enemy1;
private:
    int enemy1Tex[2];
    bool enemy_Spawn;
    bool one_Load_Tex;
    std::vector<Die_Data> die_List;
    Animation ani;
};

