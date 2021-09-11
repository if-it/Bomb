#pragma once
#include "RockAttack.h"
#include"Load.h"

class RockAttackMana :
    public Structure
{
public:
    RockAttackMana();
    ~RockAttackMana();
    void Init();
    void Loading(Load*load);
    void Update();
    void Spawn(const int num, const Vector2& sc);
    void Coll();
    void Delete_Rock();
    void Draw(const Vector2& sc, const Vector2& shake);

    std::vector<RockAttack> rock_Attack;
private:
    int tex;
};

