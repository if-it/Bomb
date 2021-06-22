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
    bool DieChack();
    Count invincible;//–³“G
    int hp;
    Vector2 fVec;
};

