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
    void AllUpdate();
    bool DieChack();
    //���G
    Count invincible;
    //���j�̖��G
    Count exInvincible;
    int hp;
    Vector2 fVec;
};

