#pragma once
#include "Enemy.h"
class Enemy1 :
    public Enemy
{
public:
    Enemy1();
    ~Enemy1();
    void Init(Vector2 pos);
    void Update();
    void MapCollUpdate(std::vector<std::vector<int>>& collMap);
    void Coll(std::vector<Explosion>& ex);
    void MoveChack(const Vector2&pos,Collision*coll);
    void Draw(const Vector2& sc, const Vector2& shake);
  
};

