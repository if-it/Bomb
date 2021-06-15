#include "Fuse.h"



Fuse::Fuse()
{
}


Fuse::~Fuse()
{
}

void Fuse::Init(std::vector<std::vector<int>>& map)
{
	fuses.clear();
	InitFuse = FUSE();
	for (int y = 0; y < (int)map.size(); ++y)
	{
		for (int x = 0; x < (int)map[y].size(); ++x)
		{
			if (map[y][x] >= 4 && map[y][x] <= 7)
			{
				InitFuse = FUSE();
				InitFuse.object.allVec.pos = Vector2((float)(SIZE * x), (float)(SIZE * y));
				InitFuse.type = map[y][x];
				InitFuse.object.dis = true;
				InitFuse.maxAnime = 1;
				InitFuse.animeFrame = 1;
				switch (InitFuse.type)
				{
				case 4:
					InitFuse.object.rote = 0;
					break;
				case 5:
					InitFuse.object.rote = 180;
					break;
				case 6:
					InitFuse.object.rote = 270;
					break;
				case 7:
					InitFuse.object.rote = 90;
					break;
				default:
					break;
				}
				fuses.push_back(InitFuse);
			}
			if (map[y][x] >= 8 && map[y][x] <= 23)
			{
				InitFuse = FUSE();
				InitFuse.object.allVec.pos = Vector2((float)(SIZE * x), (float)(SIZE * y));
				InitFuse.type = map[y][x];
				InitFuse.object.dis = true;
				InitFuse.maxAnime = 12;
				InitFuse.animeFrame = 2;
				switch (InitFuse.type)
				{

				case 8:
				case 12:
				case 20:
					InitFuse.object.rote = 0;
					break;
				case 9:
				case 15:
				case 21:
					InitFuse.object.rote = 180;
					break;
				case 10:
				case 18:
				case 22:
					InitFuse.object.rote = 270;
					break;
				case 11:
				case 17:
				case 23:
					InitFuse.object.rote = 90;
					break;
				case 13:
					InitFuse.object.lr = true;
					break;
				case 14:
					InitFuse.object.lr = true;
					InitFuse.object.rote = 180;
					break;
				case 16:
					InitFuse.object.lr = true;
					InitFuse.object.rote = 270;
					break;
				case 19:
					InitFuse.object.rote = 90;
					InitFuse.object.lr = true;
					break;
				default:
					break;
				}


				fuses.push_back(InitFuse);
			}
		}
	}

	for (int i = 0; i < (int)fuses.size(); ++i)
	{
		if (fuses[i].type >= 8 && fuses[i].type <= 23)
		{
			int y = (int)(fuses[i].object.allVec.pos.y / SIZE);
			int x = (int)(fuses[i].object.allVec.pos.x / SIZE);
			if (y - 1 >= 0 && y + 1 < (int)map.size() && x - 1 >= 0 && x + 1 < (int)map[0].size())
			{
				int mapy = 0;
				int mapx = 0;
				if (fuses[i].type == 8 || fuses[i].type == 16 || fuses[i].type == 17 || fuses[i].type == 20)
				{
					mapy = y - 1;
					if (mapy >= 0)
					{
						if (map[y - 1][x] == 0)
						{
							fuses[i].ignitionFlg = true;
						}
					}
				}
				if (fuses[i].type == 9 || fuses[i].type == 18 || fuses[i].type == 19 || fuses[i].type == 21)
				{
					mapy = y + 1;
					if (mapy < (int)map.size())
					{
						if (map[y + 1][x] == 0)
						{
							fuses[i].ignitionFlg = true;
						}
					}

				}
				if (fuses[i].type == 10 || fuses[i].type == 12 || fuses[i].type == 14 || fuses[i].type == 22)
				{
					mapx = x - 1;
					if (mapx >= 0)
					{
						if (map[y][x - 1] == 0)
						{
							fuses[i].ignitionFlg = true;
						}
					}
				}
				if (fuses[i].type == 11 || fuses[i].type == 13 || fuses[i].type == 15 || fuses[i].type == 23)
				{
					mapx = x + 1;
					if (mapx < (int)map[0].size())
					{
						if (map[y][x + 1] == 0)
						{
							fuses[i].ignitionFlg = true;
						}
					}
				}
			}

		}
	}
}

void Fuse::Update(std::vector<std::vector<int>>& map, BombMana* bombMana)
{
	for (int i = 0; i < (int)fuses.size(); ++i)
	{
		if (fuses[i].coll)
		{
			if (fuses[i].anime.OneAnimation(fuses[i].animeFrame, fuses[i].maxAnime))
			{
				if (!fuses[i].animeEnd)
				{
					fuses[i].animeEnd = true;

					switch (fuses[i].type)
					{
					case 4:// 4 è„ëÂñC
						bombMana->BombSpawn(Vector2(fuses[i].object.allVec.pos.x, fuses[i].object.allVec.pos.y - SIZE), 
							Vector2(0.0f, -BSPEED),false);
						break;
					case 5:// 5 â∫ëÂñC
						bombMana->BombSpawn(Vector2(fuses[i].object.allVec.pos.x, fuses[i].object.allVec.pos.y + SIZE),
							Vector2(0.0f, BSPEED),false);
						break;
					case 6:// 6 ç∂ëÂñC
						bombMana->BombSpawn(Vector2(fuses[i].object.allVec.pos.x - SIZE, fuses[i].object.allVec.pos.y), 
							Vector2(-BSPEED, 0.0f),false);
						break;
					case 7:// 7 âEëÂñC
						bombMana->BombSpawn(Vector2(fuses[i].object.allVec.pos.x + SIZE, fuses[i].object.allVec.pos.y), 
							Vector2(BSPEED, 0.0f),false);
						break;
					case 8:// 8 è„ì±âŒê¸
					case 14:// 14 ç∂â∫äp
					case 15:// 15 âEâ∫äp
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x, fuses[i].object.allVec.pos.y + SIZE), map);
						break;
					case 9:// 9 â∫ì±âŒê¸
					case 12:// 12 ç∂è„äp
					case 13:// 13 âEè„äp
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x, fuses[i].object.allVec.pos.y - SIZE), map);
						break;
					case 10:// 10 ç∂ì±âŒê¸
					case 17:// 17 è„âEäp
					case 19:// 19 â∫âEäp
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x + SIZE, fuses[i].object.allVec.pos.y), map);
						break;
					case 11:// 11 âEì±âŒê¸
					case 16:// 16 è„ç∂äp
					case 18:// 18 â∫ç∂äp
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x - SIZE, fuses[i].object.allVec.pos.y), map);
						break;
					case 20:// 20 è„âEç∂
					case 21:// 21 â∫ç∂âE
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x + SIZE, fuses[i].object.allVec.pos.y), map);
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x - SIZE, fuses[i].object.allVec.pos.y), map);
						break;
					case 22:// 22 ç∂è„â∫
					case 23:// 23 âEâ∫è„
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x, fuses[i].object.allVec.pos.y + SIZE), map);
						NextAnimation(Vector2(fuses[i].object.allVec.pos.x, fuses[i].object.allVec.pos.y - SIZE), map);
						break;
					default:
						break;
					}
				}
				else
				{
					fuses[i].animeEndCount++;
					if (fuses[i].animeEndCount == 60 * 4)
					{
						fuses[i].animeEndCount = 0;
						fuses[i].animeEnd = false;
						fuses[i].anime = ANIMATION();
						fuses[i].coll = false;
					}
				}
			}
		}
	}
}

//void Fuse::BombSpawn(std::vector<Bomb>& bomb, Vector2 set_pos, Vector2 set_vec)
//{
//	static Bomb InitBomb;
//
//	InitBomb.Init();
//	InitBomb.game_object.dis = true;
//	InitBomb.game_object.allVec.pos = set_pos;
//	InitBomb.game_object.allVec.vec = set_vec;
//	PlaySoundMem(bombSound, DX_PLAYTYPE_BACK, true);
//
//	bomb.push_back(InitBomb);
//
//	/*for (int i = 0;i < (int)bomb.size();++i)
//	{
//		if (!bomb[i].game_object.dis)
//		{
//			bomb[i].Init();
//			bomb[i].game_object.dis = true;
//			bomb[i].game_object.allVec.pos = set_pos;
//			bomb[i].game_object.allVec.vec = set_vec;
//			PlaySoundMem(bombSound, DX_PLAYTYPE_BACK, true);
//			break;
//		}
//	}*/
//}

void Fuse::NextAnimation(Vector2 nextPos, std::vector<std::vector<int>>& map)
{
	int nextMap = map[(int)(nextPos.y / SIZE)][(int)(nextPos.x / SIZE)];

	if (nextMap >= 4 && nextMap <= 23)
	{
		for (int i = 0; i < (int)fuses.size(); ++i)
		{
			if (fuses[i].object.allVec.pos == nextPos)
			{
				fuses[i].coll = true;
				fuses[i].anime.counter.flg = false;
			}
		}
	}
}





void Fuse::Coll(Collision* coll, Vector2 pos, int size)
{
	for (int i = 0; i < (int)fuses.size(); ++i)
	{
		if (fuses[i].type >= 8 && fuses[i].type <= 23)
		{

			if (fuses[i].ignitionFlg && !fuses[i].coll && coll->Collsion(fuses[i].object.allVec.pos, SIZE, SIZE, pos, size, size))
			{
				fuses[i].coll = true;
				fuses[i].anime.counter.flg = false;
			}
		}
	}
}



void Fuse::Draw(const Vector2& sc, const Vector2& shake)
{
	for (int i = 0; i < (int)fuses.size(); ++i)
	{
		if (fuses[i].type >= 4 && fuses[i].type <= 7)
		{
			DrawRotaTex(fuses[i].object, cannonTex, true, shake, sc);
		}
		else if (fuses[i].type >= 8 && fuses[i].type <= 11)
		{
			DrawRotaTex(fuses[i].object, lineTex[fuses[i].anime.num], true, shake, sc);
		}
		else if (fuses[i].type >= 12 && fuses[i].type <= 19)
		{
			DrawRotaTex(fuses[i].object, curveTex[fuses[i].anime.num], true, shake, sc);
		}
		else if (fuses[i].type >= 20 && fuses[i].type <= 23)
		{
			DrawRotaTex(fuses[i].object, wTex[fuses[i].anime.num], true, shake, sc);
		}
		/*	switch (fuses[i].type)
			{
			case 4:
			case 5:
			case 6:
			case 7:
				DrawRotaTex(fuses[i].object, cannonTex, true, shake, sc);
				break;
			case 8:
			case 9:
			case 10:
			case 11:
				DrawRotaTex(fuses[i].object, lineTex[fuses[i].anime.num], true, shake, sc);
				break;
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
				DrawRotaTex(fuses[i].object, curveTex[fuses[i].anime.num], true, shake, sc);
				break;
			default:
				break;
			}*/

	}
}
