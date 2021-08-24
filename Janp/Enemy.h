#pragma once
#include "MapColl.h"
#include"Collision.h"
#include"Explosion.h"

class Enemy :
    public MapColl
{
public:
    Enemy();
    ~Enemy();
    void Damage(int damage);

protected:
    void EnemyAllUpdate(const float Enemy_Speed, const float Enemy_Max_Speed);
    bool DieChack();
    //–³“G
    Count invincible;
    //”š”j‚Ì–³“G
    Count exInvincible;
    int hp;
    Vector2 fVec;
};

