#pragma once
#include"Load.h"
#include"SideExplosion.h"
class SideExplosionMana :
    public MapColl
{
public:
    SideExplosionMana();
    ~SideExplosionMana();
    void Init();
    void Loading(Load*load);
    void Update(const bool& explosion_on, const Vector2& set_pos,std::vector<std::vector<int>>& collMap, bool& shakeflg);
    void Draw(const Vector2& sc, const Vector2& shake);

    std::vector<SideExplosion> sideEx;
private:
    int tex[16];
    Animation ani;
    bool spawn;
    Count end;
};

