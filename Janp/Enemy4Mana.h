#pragma once
#include "MapColl.h"
#include"Load.h"
#include"Enemy4.h"
using Die_Data = Enemy::Die_Data;

class Enemy4Mana :
    public MapColl
{
public:
    Enemy4Mana();
    ~Enemy4Mana();
    void Init(std::vector<std::vector<int>>& collMap, Load* load, const int& stage);
    void Save();
    void Update(RockEffectMana* rockEffe, HpDropItemMana* hpItemMana);
    void MapCollUpdate(std::vector<std::vector<int>>& collMap);
    void MoveChack(const Vector2& pos, Collision* coll);
    void Coll(std::vector<Explosion>& ex);
    void Draw(const Vector2& sc, const Vector2& shake);

    std::vector<Enemy4> enemy4;
private:
    Animation ani;   
    int tex;
    bool enemy_Spawn;
    bool one_Load_Tex;
    std::vector<Die_Data> die_List;
};

