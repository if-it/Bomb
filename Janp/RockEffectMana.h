#pragma once
#include"Load.h"
#include"RockEffect.h"

class RockEffectMana :
    public Draw
{
public:
    RockEffectMana();
    ~RockEffectMana();
    void Init();
    void Loading(Load* load);
    void Update();
    void Spawn(const Vector2&pos,const int num);
    void Draw(const Vector2& sc, const Vector2& shake);

private:
    std::vector<RockEffect> rock;
    int tex[3];
};

