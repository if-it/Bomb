#pragma once
#include "MapColl.h"
class Enemy :
    public MapColl
{
public:
    Enemy();
    ~Enemy();
    void ExColl(int damage);

protected:
    void DieChack();
    Count invincible;//–³“G
    int hp;
};

