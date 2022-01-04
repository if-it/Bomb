#pragma once
#include "BombBlowEffect.h"
class BombBlowEffectMana :
    public BombBlowEffect
{
public:
    BombBlowEffectMana();
    ~BombBlowEffectMana();
    void Init();
    void Loading(int& duat);
    void Update(const bool& flg, const Vector2& pos);
    void Draw(const Vector2& sc, const Vector2& shake);
private:
    int tex;
    void Spawn(const Vector2& pos);
    std::vector<BombBlowEffect> bomb_Blow_Effect;
    int count;
    bool spawn_Flg;
};

