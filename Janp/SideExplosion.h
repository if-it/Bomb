#pragma once
#include "MapColl.h"
class SideExplosion :
    public MapColl
{
public:
    SideExplosion();
    ~SideExplosion();
    void Init(const Vector2& set_pos, const std::string& NameTag);
    void Update();
    bool SizeSub();
    void Draw(const Vector2& sc, const Vector2& shake, const int& tex);
};

