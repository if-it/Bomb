#pragma once
#include "Draw.h"
#include"Load.h"
#include"Item.h"

using Save_Data = Item::Save_Data;

class ItemMana :
    public Draw
{
public:
    ItemMana();
    ~ItemMana();


    void SaveData_Load(std::vector<std::vector<int>>& map, const int& data_Num, const int& stage);
    void Save_Data_Init();
    void Save(const int& data_Num);

    void Init(std::vector<std::vector<int>>& map,const int& stage);
    void Loading(Load* load);
    void Update();
    void Coll( int& get_Item);
    void Draw(const Vector2& sc, const Vector2& shake);

    std::vector<Item> item;
    int tex[5];
private:
    Animation item_Ani;
    std::vector<Save_Data> save_Data_Ori;
    int save_Data_Size;
    int ani_Num[5];
    bool one_Ani;
};

