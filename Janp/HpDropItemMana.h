#pragma once
#include "HpDropItem.h"
#include"Load.h"
class HpDropItemMana :
	public HpDropItem
{
public:
	HpDropItemMana();
	~HpDropItemMana();
	void Init();
	void Loading(Load* load);
	void Spawn(Vector2 pos);
	void Update();
	void Coll();
	int NowNum();
	void Draw(const Vector2& sc, const Vector2& shake);

	std::vector<HpDropItem> hpDropItem;
private:
	int tex;
};

