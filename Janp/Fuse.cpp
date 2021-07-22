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
				InitFuse.object.game.allVec.pos = Vector2((float)(SIZE * x), (float)(SIZE * y));
				InitFuse.type = map[y][x];
				InitFuse.object.game.dis = true;
				InitFuse.maxAnime = 1;
				InitFuse.animeFrame = 1;
				InitFuse.map_num = 0;
				InitFuse.ignitionFlg = false;
				switch (InitFuse.type)
				{
				case 4:
					InitFuse.object.game.rote = 0;
					break;
				case 5:
					InitFuse.object.game.rote = 180;
					break;
				case 6:
					InitFuse.object.game.rote = 270;
					break;
				case 7:
					InitFuse.object.game.rote = 90;
					break;
				default:
					break;
				}
				fuses.push_back(InitFuse);
			}
			if ((map[y][x] >= 8 && map[y][x] <= 23) || (map[y][x] >= 54 && map[y][x] <= 57))
			{
				InitFuse = FUSE();
				InitFuse.object.game.allVec.pos = Vector2((float)(SIZE * x), (float)(SIZE * y));
				InitFuse.type = map[y][x];
				InitFuse.object.game.dis = true;
				InitFuse.maxAnime = 12;
				InitFuse.animeFrame = 1;
				InitFuse.ignitionFlg = false;
				switch (InitFuse.type)
				{

				case 8:
				case 12:
				case 20:
				case 54:
					InitFuse.object.game.rote = 0;
					break;
				case 9:
				case 15:
				case 21:
				case 57:
					InitFuse.object.game.rote = 180;
					break;
				case 10:
				case 18:
				case 22:
					InitFuse.object.game.rote = 270;
					break;
				case 11:
				case 17:
				case 23:
					InitFuse.object.game.rote = 90;
					break;
				case 13:
				case 56:
					InitFuse.object.game.lr = true;
					break;
				case 14:
				case 55:
					InitFuse.object.game.lr = true;
					InitFuse.object.game.rote = 180;
					break;
				case 16:
					InitFuse.object.game.lr = true;
					InitFuse.object.game.rote = 270;
					break;
				case 19:
					InitFuse.object.game.rote = 90;
					InitFuse.object.game.lr = true;
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
		if ((fuses[i].type >= 8 && fuses[i].type <= 23) || (fuses[i].type >= 54 && fuses[i].type <= 57))
		{
			int y = (int)(fuses[i].object.game.allVec.pos.y / SIZE);
			int x = (int)(fuses[i].object.game.allVec.pos.x / SIZE);
			int map_num[6] = { y - 1,y,y + 1,x - 1,x,x + 1 };
			if (y - 1 >= 0 && y + 1 < (int)map.size() && x - 1 >= 0 && x + 1 < (int)map[0].size())
			{

				if (fuses[i].type == 8 || fuses[i].type == 16 || fuses[i].type == 17 || fuses[i].type == 20)
				{
					if (map[map_num[0]][x] == 0)
					{
						InitFuse.ignitionFlg = true;
					}

				}
				if (fuses[i].type == 9 || fuses[i].type == 18 || fuses[i].type == 19 || fuses[i].type == 21)
				{


					if (map[map_num[2]][x] == 0)
					{
						InitFuse.ignitionFlg = true;
					}


				}
				if (fuses[i].type == 10 || fuses[i].type == 12 || fuses[i].type == 14 || fuses[i].type == 22 ||
					fuses[i].type == 56 || fuses[i].type == 57)
				{
					if (map[y][map_num[3]] == 0)
					{
						InitFuse.ignitionFlg = true;
					}

				}
				if (fuses[i].type == 11 || fuses[i].type == 13 || fuses[i].type == 15 || fuses[i].type == 23 ||
					fuses[i].type == 54 || fuses[i].type == 55)
				{

					if (map[y][map_num[5]] == 0)
					{
						InitFuse.ignitionFlg = true;
					}
				}


			}

			bool map_check[3][3] = { {0,0,0},{0,0,0},{0,0,0} };

			bool map_over[6] = { 0,1,0,0,1,0 };

			if (map_num[0] >= 0)
			{
				map_over[0] = true;
			}
			if (map_num[2] < (int)map.size())
			{
				map_over[2] = true;
			}
			if (map_num[3] >= 0)
			{
				map_over[3] = true;
			}
			if (map_num[5] < (int)map[0].size())
			{
				map_over[5] = true;
			}

			for (int n = 0; n < 3; ++n)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (map_over[n] && map_over[3+j] && map[map_num[n]][map_num[3+j]] != 0)
					{
						map_check[n][j] = true;
					}
				}
			}

		/*	if (map_over[0]&& map_over[2]&&map[map_num[0]][map_num[2]]!=0)
			{
				map_check[0][0] = true;
			}
			if (map_over[0] && map[map_num[0]][x] != 0)
			{
				map_check[0][1] = true;
			}
			if (map_over[0]&&map_over[3] && map[map_num[0]][map_num[3]] != 0)
			{
				map_check[0][2] = true;
			}
			if ( map_over[2] && map[map_num[0]][map_num[2]] != 0)
			{
				map_check[0][0] = true;
			}*/

		}
	}
}

void Fuse::Loading(Load* load, int* mapTexC)
{
	load->LoadAnimeTex("Load/Texture/Fuse/LineFuse.png", 12, 12, 1, SIZE, SIZE, lineTex);
	load->LoadAnimeTex("Load/Texture/Fuse/CurveFuse.png", 12, 12, 1, SIZE, SIZE, curveTex);
	load->LoadAnimeTex("Load/Texture/Fuse/WFuse.png", 12, 12, 1, SIZE, SIZE, wTex1);
	load->LoadAnimeTex("Load/Texture/Fuse/WFuse2.png", 12, 12, 1, SIZE, SIZE, wTex2);
	load->LoadTex("Load/Texture/Fuse/Cannon.png", cannonTex);
	mapTex = mapTexC;
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
						bombMana->BombSpawn(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y - SIZE),
							Vector2(0.0f, -BSPEED), false, 1);
						break;
					case 5:// 5 â∫ëÂñC
						bombMana->BombSpawn(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y + SIZE),
							Vector2(0.0f, BSPEED), false, 1);
						break;
					case 6:// 6 ç∂ëÂñC
						bombMana->BombSpawn(Vector2(fuses[i].object.game.allVec.pos.x - SIZE, fuses[i].object.game.allVec.pos.y),
							Vector2(-BSPEED, 0.0f), false, 1);
						break;
					case 7:// 7 âEëÂñC
						bombMana->BombSpawn(Vector2(fuses[i].object.game.allVec.pos.x + SIZE, fuses[i].object.game.allVec.pos.y),
							Vector2(BSPEED, 0.0f), false, 1);
						break;
					case 8:// 8 è„ì±âŒê¸
					case 14:// 14 ç∂â∫äp
					case 15:// 15 âEâ∫äp
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y + SIZE), map);
						break;
					case 9:// 9 â∫ì±âŒê¸
					case 12:// 12 ç∂è„äp
					case 13:// 13 âEè„äp
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y - SIZE), map);
						break;
					case 10:// 10 ç∂ì±âŒê¸
					case 17:// 17 è„âEäp
					case 19:// 19 â∫âEäp
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x + SIZE, fuses[i].object.game.allVec.pos.y), map);
						break;
					case 11:// 11 âEì±âŒê¸
					case 16:// 16 è„ç∂äp
					case 18:// 18 â∫ç∂äp
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x - SIZE, fuses[i].object.game.allVec.pos.y), map);
						break;
					case 20:// 20 è„âEç∂
					case 21:// 21 â∫ç∂âE
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x + SIZE, fuses[i].object.game.allVec.pos.y), map);
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x - SIZE, fuses[i].object.game.allVec.pos.y), map);
						break;
					case 22:// 22 ç∂è„â∫
					case 23:// 23 âEâ∫è„
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y + SIZE), map);
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y - SIZE), map);
						break;
					case 54:
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y - SIZE), map);
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x + SIZE, fuses[i].object.game.allVec.pos.y), map);
					case 55:
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y + SIZE), map);
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x + SIZE, fuses[i].object.game.allVec.pos.y), map);
						break;
					case 56:
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y - SIZE), map);
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x - SIZE, fuses[i].object.game.allVec.pos.y), map);
						break;
					case 57:
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x, fuses[i].object.game.allVec.pos.y + SIZE), map);
						NextAnimation(Vector2(fuses[i].object.game.allVec.pos.x - SIZE, fuses[i].object.game.allVec.pos.y), map);
						break;
						break;
					default:
						break;
					}
				}
				else
				{
					fuses[i].animeEndCount++;
					if (fuses[i].animeEndCount == 60 * 6)
					{
						fuses[i].animeEndCount = 0;
						fuses[i].animeEnd = false;
						fuses[i].anime = Animation();
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

	if ((nextMap >= 4 && nextMap <= 23) || (nextMap >= 54 && nextMap <= 57))
	{
		for (int i = 0; i < (int)fuses.size(); ++i)
		{
			if (fuses[i].object.game.allVec.pos == nextPos)
			{
				fuses[i].coll = true;
				fuses[i].anime.counter.flg = false;
			}
		}
	}
}


void Fuse::Coll(Collision* coll, const GameObject& obj)
{
	for (int i = 0; i < (int)fuses.size(); ++i)
	{
		if ((fuses[i].type >= 8 && fuses[i].type <= 23) || (fuses[i].type >= 54 && fuses[i].type <= 57))
		{

			if (InitFuse.ignitionFlg && !fuses[i].coll &&
				coll->CollsionObj(fuses[i].object, obj))
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
			DrawTex(fuses[i].object, mapTex[fuses[i].map_num], true, shake, sc);
			DrawRotaTex(fuses[i].object, lineTex[fuses[i].anime.num], true, shake, sc);
		}
		else if (fuses[i].type >= 12 && fuses[i].type <= 19)
		{
			DrawTex(fuses[i].object, mapTex[fuses[i].map_num], true, shake, sc);
			DrawRotaTex(fuses[i].object, curveTex[fuses[i].anime.num], true, shake, sc);
		}
		else if (fuses[i].type >= 20 && fuses[i].type <= 23)
		{
			DrawTex(fuses[i].object, mapTex[fuses[i].map_num], true, shake, sc);
			DrawRotaTex(fuses[i].object, wTex1[fuses[i].anime.num], true, shake, sc);
		}
		else if (fuses[i].type >= 54 && fuses[i].type <= 57)
		{
			DrawTex(fuses[i].object, mapTex[fuses[i].map_num], true, shake, sc);
			DrawRotaTex(fuses[i].object, wTex2[fuses[i].anime.num], true, shake, sc);
		}
	}
}
