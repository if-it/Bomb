#pragma once
#include "Enemy.h"
#include"Collision.h"
class Enemy1 :
    public Enemy
{
public:
    Enemy1();
    ~Enemy1();
    void Init(Vector2 pos);
    void Update();
    void MapCollUpdate(std::vector<std::vector<int>>& collMap);
    void PlayerColl();
    void MoveChack(const Vector2&pos,Collision*coll);
    void Draw(const Vector2& sc, const Vector2& shake);
private:
    void Map_Coll(std::vector<std::vector<int>>& collMap);
    void MapJub(const int& mapPoint, const int& pointNum);
  
};

