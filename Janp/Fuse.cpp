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
					InitFuse.object.game.rota = 0;
					break;
				case 5:
					InitFuse.object.game.rota = 180;
					break;
				case 6:
					InitFuse.object.game.rota = 270;
					break;
				case 7:
					InitFuse.object.game.rota = 90;
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
					InitFuse.object.game.rota = 0;
					break;
				case 9:
				case 15:
				case 21:
				case 57:
					InitFuse.object.game.rota = 180;
					break;
				case 10:
				case 18:
				case 22:
					InitFuse.object.game.rota = 270;
					break;
				case 11:
				case 17:
				case 23:
					InitFuse.object.game.rota = 90;
					break;
				case 13:
				case 56:
					InitFuse.object.game.lr = true;
					break;
				case 14:
				case 55:
					InitFuse.object.game.lr = true;
					InitFuse.object.game.rota = 180;
					break;
				case 16:
					InitFuse.object.game.lr = true;
					InitFuse.object.game.rota = 270;
					break;
				case 19:
					InitFuse.object.game.rota = 90;
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
						fuses[i].ignitionFlg = true;
					}

				}
				if (fuses[i].type == 9 || fuses[i].type == 18 || fuses[i].type == 19 || fuses[i].type == 21)
				{


					if (map[map_num[2]][x] == 0)
					{
						fuses[i].ignitionFlg = true;
					}


				}
				if (fuses[i].type == 10 || fuses[i].type == 12 || fuses[i].type == 14 || fuses[i].type == 22 ||
					fuses[i].type == 56 || fuses[i].type == 57)
				{
					if (map[y][map_num[3]] == 0)
					{
						fuses[i].ignitionFlg = true;
					}

				}
				if (fuses[i].type == 11 || fuses[i].type == 13 || fuses[i].type == 15 || fuses[i].type == 23 ||
					fuses[i].type == 54 || fuses[i].type == 55)
				{

					if (map[y][map_num[5]] == 0)
					{
						fuses[i].ignitionFlg = true;
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
					if (map_over[n] && map_over[3 + j] && map[map_num[n]][map_num[3 + j]] != 0 &&
						!(map[map_num[n]][map_num[3 + j]] >= 73 && map[map_num[n]][map_num[3 + j]] <= 77) &&
						!(map[map_num[n]][map_num[3 + j]] >= 4 && map[map_num[n]][map_num[3 + j]] <= 7))
					{
						map_check[n][j] = true;
					}
				}
			}

			fuses[i].map_num = 101010;
			for (int n = 0; n < 3; ++n)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (map_check[n][j])
					{
						if (n == 1 && j == 1)
						{
							continue;
						}
						if (n == 0)
						{
							fuses[i].map_num += (j + 2) * 10000;
						}
						else if (n == 1)
						{
							fuses[i].map_num += (j + 2) * 100;
						}
						else
						{
							fuses[i].map_num += j + 2;
						}
					}
				}
			}

			switch (fuses[i].map_num)
			{
			case 101010:
			case 101012:
			case 101014:
			case 101016:
			case 121014:
			case 121016:
			case 121010:
			case 121012:
			case 141010:
			case 141012:
			case 141014:
			case 141016:
			case 161010:
			case 161012:
			case 161014:
			case 161016:
				//å«óß
				fuses[i].map_num = 21;
				break;
			case 101213:
			case 101217:
			case 101413:
			case 101415:
			case 101615:
			case 101617:
			case 101613:
			case 121213:
			case 121413:
			case 121415:
			case 131617:
			case 131410:
			case 131412:
			case 131414:
			case 131210:
			case 131212:
			case 131213:
			case 131214:
			case 131215:
			case 131216:
			case 131217:
			case 131219:
			case 131610:
			case 131612:
			case 131619:
			case 131413:
			case 131415:
			case 131614:
			case 131615:
			case 131416:
			case 131417:
			case 131613:
			case 131616:
			case 141213:
			case 141217:
			case 141413:
			case 141415:
			case 141613:
			case 151010:
			case 151213:
			case 151410:
			case 151412:
			case 151413:
			case 151415:
			case 151610:
			case 151612:
			case 151613:
			case 151615:
			case 161213:
			case 161217:
			case 161413:
			case 161415:
			case 161613:
			case 161615:
			case 161617:
			case 171210:
			case 171212:
			case 171213:
			case 171214:
			case 171215:
			case 171216:
			case 171217:
			case 171219:
			case 171413:
			case 171415:
			case 171610:
			case 171612:
			case 171613:
			case 171614:
			case 171615:
			case 171616:
			case 171617:
			case 191213:
			case 191413:
			case 191415:
			case 191613:
			case 191619:
				//ñÑÇ‹Ç¡ÇƒÇÈ
				fuses[i].map_num = 0;
				break;
			case 101210:
			case 101212:
			case 101214:
			case 101216:
			case 121210:
			case 121212:
			case 121214:
			case 121216:
			case 141210:
			case 141212:
			case 141214:
			case 141216:
			case 161210:
			case 161212:
			case 161214:
			case 161216:
				//1É}ÉXâE
				fuses[i].map_num = 19;
				break;
			case 101410:
			case 101412:
			case 101414:
			case 101416:
			case 121410:
			case 121412:
			case 121414:
			case 121416:
			case 141410:
			case 141412:
			case 141414:
			case 141416:
			case 161410:
			case 161412:
			case 161414:
			case 161416:
				//1É}ÉXç∂
				fuses[i].map_num = 20;
				break;
			case 101619:
			case 121613:
			case 121615:
			case 121617:
			case 121619:
			case 141615:
			case 141617:
			case 141619:
			case 161619:
				//è„
				fuses[i].map_num = 1;
				break;
			case 101013:
			case 101015:
			case 101017:
			case 101019:
			case 121013:
			case 121015:
			case 121017:
			case 121019:
			case 141013:
			case 141015:
			case 141017:
			case 141019:
			case 161013:
			case 161015:
			case 161017:
			case 161019:
				//1É}ÉXècè„
				fuses[i].map_num = 17;
				break;
			case 101610:
			case 101612:
			case 101614:
			case 101616:
			case 121610:
			case 121612:
			case 121614:
			case 121616:
			case 141610:
			case 141612:
			case 141614:
			case 141616:
			case 161610:
			case 161612:
			case 161614:
			case 161616:
				//1É}ÉXê^ÇÒíÜâ°
				fuses[i].map_num = 16;
				break;
			case 131013:
			case 131015:
			case 131017:
			case 131019:
			case 151013:
			case 151015:
			case 171013:
			case 171015:
			case 171017:
			case 171019:
			case 191013:
			case 191015:
			case 191017:
			case 191019:
				//1É}ÉXê^ÇÒíÜèc
				fuses[i].map_num = 15;
				break;
			case 131010:
			case 131012:
			case 131014:
			case 131016:
			case 151012:
			case 151014:
			case 151016:
			case 151017:
			case 151019:
			case 171010:
			case 171012:
			case 171014:
			case 171016:
			case 191010:
			case 191012:
			case 191014:
			case 191016:
				//1É}ÉXècâ∫
				fuses[i].map_num = 18;
				break;
			case 101215:
			case 101219:
			case 121215:
			case 121217:
			case 121219:
			case 141215:
			case 141219:
			case 161215:
			case 161219:
				//âEè„äp1
				fuses[i].map_num = 7;
				break;
			case 151210:
			case 151212:
			case 151214:
			case 151216:
			case 191210:
			case 191212:
			case 191214:
			case 191216:
			case 151614:
				//âEâ∫äp1
				fuses[i].map_num = 9;
				break;
			case 101417:
			case 101419:
			case 121417:
			case 121419:
			case 131419:
			case 141417:
			case 141419:
			case 151414:
			case 151416:
			case 161417:
			case 161419:
				//ç∂è„äp1
				fuses[i].map_num = 8;
				break;

			case 151215:
			case 151217:
			case 151219:
			case 191215:
			case 191217:
			case 191219:
				//âE
				fuses[i].map_num = 5;
				break;
			case 151617:
			case 151619:
				//ç∂è„äp2
				fuses[i].map_num = 12;
				break;
			case 151417:
			case 151419:
			case 171417:
			case 171419:
			case 191417:
			case 191419:
				//ç∂
				fuses[i].map_num = 6;
				break;
			case 171410:
			case 171412:
			case 171414:
			case 171416:
			case 191410:
			case 191412:
			case 191414:
			case 191416:
				//ç∂â∫äp1
				fuses[i].map_num = 10;
				break;
			case 151616:
			case 191610:
			case 191612:
			case 191614:
			case 191616:
				//â∫
				fuses[i].map_num = 4;
				break;
			case 171619:
				//âEè„äp2
				fuses[i].map_num = 11;
				break;
			case 191615:
				//âEâ∫äp2
				fuses[i].map_num = 13;
				break;
			case 191617:
				//ç∂â∫äp2
				fuses[i].map_num = 14;
				break;
			default:
				fuses[i].map_num = 0;
				break;
			}


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

			if (fuses[i].ignitionFlg && !fuses[i].coll &&
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
