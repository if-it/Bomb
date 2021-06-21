#pragma once
#include "Draw.h"
#include"BombMana.h"
#include"Collision.h"

class Fuse :public Draw
{
public:
	Fuse();
	~Fuse();
	void Init(std::vector<std::vector<int>>& collMap);
	void Update(std::vector<std::vector<int>>& collMap, BombMana* bombMana);
	void Coll(Collision*coll,const GameObject& obj);
	void Draw(const Vector2& sc, const Vector2& shake);
	int lineTex[12];
	int curveTex[12];
	int wTex[12];
	int cannonTex;
private :
	//void BombSpawn(std::vector<Bomb>& bomb,Vector2 set_pos, Vector2 set_vec);
	void NextAnimation(Vector2 nextPos, std::vector<std::vector<int>>& collMap);
	struct FUSE
	{
		GameObject object;
		ANIMATION anime;
		int type;
		bool coll;
		bool animeEnd;
		bool ignitionFlg;
		int maxAnime;
		int animeFrame;
		int animeEndCount;
		FUSE()
		{
			object = GameObject("fuse",false);
			anime = ANIMATION();
			type = 0;
			coll = false;
			animeEnd = false;
			ignitionFlg = false;
			maxAnime = 0;
			animeFrame = 0;
			animeEndCount = 0;
		}
	};
	FUSE InitFuse;
	std::vector<FUSE> fuses;
};

