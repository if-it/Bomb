#include "Explosion.h"

Explosion::Explosion()
{
	for (int i = 0; i < 9; ++i)
	{
		yNum[i] = 0;
		xNum[i] = 0;
	}
	damage = 0;
	spawn = false;
	time = 0;
}

Explosion::~Explosion()
{
}

void Explosion::Init()
{
	boxObj.clear();
	boxTime.clear();
	boxFlg.clear();
	game_object = GameObject("ex", false, Vector2(64.0f, 64.0f));
	exAni = Animation();
	spawn = false;
	time = 0;
	//game_object.allVec.pos = go.allVec.pos;
	for (int i = 0; i < EXNUM; ++i)
	{
		exs[i] = GameObject("ex2", false, Vector2(16.0f, 16.0f));
	}
	damage = 1;
	dis2 = false;
	exspal = 255;
}

void Explosion::Update()
{
	if (game_object.game.dis || dis2)
	{
		if (!spawn)
		{

			Vector2 spos = game_object.game.allVec.pos;

			spawn = true;
			for (int i = 0; i < EXNUM; ++i)
			{
				exs[i].game.dis = true;
				exs[i].game.allVec.pos = Vector2((float)(spos.x + GetRand(game_object.game.size.x / 2)),
					(float)(spos.y + GetRand(game_object.game.size.y / 2)));
				exs[i].game.allVec.vec = Vector2((float)GetRand(3) - (float)GetRand(3), (float)GetRand(3) - (float)GetRand(3));
				if (i < 6)
				{
					exs[i].color = COLOR(100, 100, 100);
				}
			}
			int boxNum = 0;
			boxNum = GetRand(2);
			boxNum += 4;
			for (int i = 0; i < boxNum; ++i)
			{
				boxTime.push_back(0);
				boxFlg.push_back(true);
				GameObject InitBox;
				InitBox = GameObject("exBox", true, Vector2(1.0f, 1.0f), Vector2(4.0f, 4.0f));
				InitBox.game.allVec.pos = Vector2((float)(spos.x + game_object.game.size.x / 2), (float)(spos.y + game_object.game.size.y / 2));
				InitBox.game.allVec.vec = exs[i].game.allVec.vec = Vector2((float)GetRand(3) - (float)GetRand(3), -(float)(GetRand(2) + 1));
				InitBox.game.pal = 255;
				InitBox.color = COLOR(0, 0, 0);
				boxObj.push_back(InitBox);
			}
		}
		else
		{
			for (int i = 0; i < EXNUM; ++i)
			{
				//exs[i].allVec.AddPos();
				exs[i].game.pal -= 3;
			}
			for (int i = 0; i < (int)boxObj.size(); ++i)
			{
				if (!boxFlg[i])boxObj[i].game.pal -= 3;
				else {
					boxObj[i].game.allVec.vec.y += 0.1f;
					boxObj[i].game.allVec.AddPos();
					boxTime[i]++;
				}
				if (boxTime[i] == 2)
				{
					boxTime[i] = 0;
					boxTime.push_back(0);
					boxFlg.push_back(false);
					GameObject box2 = GameObject();
					box2 = boxObj[i];
					box2.game.pal = 120;
					box2.color = COLOR(120, 120, 120);
					boxObj.push_back(box2);

				}
			}
			exspal -= 3;
			if (exAni.OneAnimation(3, 12))
			{
				game_object = GameObject("ex", false);

				for (int i = 0; i < EXNUM; ++i)
				{
					exs[i] = GameObject("ex2", false);
				}
				if (exspal <= 0)
				{
					dis2 = false;
					boxObj.clear();
					boxTime.clear();
					boxFlg.clear();
				}
			}
		}
	}
}

void Explosion::Map_Coll_Update(std::vector<std::vector<int>>& collMap, BlockParticleMana* blockParticleMana)
{
	if (game_object.game.dis)Map_Coll(collMap, blockParticleMana);
}

void Explosion::Coll(Collision* coll, ALLVECTOR all, Vector2 size)
{
}


void Explosion::Map_Coll(std::vector<std::vector<int>>& collMap, BlockParticleMana* blockParticleMana)
{
	static int SizeCut = 0;
	//上左
	MapJub(MapPointer(SizeCut + 1, SizeCut + 1, collMap, xNum[0], yNum[0]), 0, collMap, blockParticleMana);

	//上真ん中
	MapJub(MapPointer(game_object.game.size.x / 2, SizeCut + 1, collMap, xNum[1], yNum[1]), 1, collMap, blockParticleMana);

	//上右
	MapJub(MapPointer(game_object.game.size.x - SizeCut - 1, SizeCut + 1, collMap, xNum[2], yNum[2]), 2, collMap, blockParticleMana);

	//右真ん中
	MapJub(MapPointer(game_object.game.size.x - SizeCut - 1, game_object.game.size.y / 2, collMap, xNum[3], yNum[3]), 3, collMap, blockParticleMana);

	//中心
	MapJub(MapPointer((game_object.game.size.x - SizeCut) / 2, (game_object.game.size.y - SizeCut) / 2, collMap, xNum[4], yNum[4]), 4, collMap, blockParticleMana);

	//左真ん中
	MapJub(MapPointer(SizeCut + 1, game_object.game.size.y / 2, collMap, xNum[5], yNum[5]), 5, collMap, blockParticleMana);

	//下左
	MapJub(MapPointer(SizeCut + 1, game_object.game.size.y - SizeCut - 1, collMap, xNum[6], yNum[6]), 6, collMap, blockParticleMana);

	//下真ん中
	MapJub(MapPointer(game_object.game.size.x / 2, game_object.game.size.y - SizeCut - 1, collMap, xNum[7], yNum[7]), 7, collMap, blockParticleMana);

	//下右
	MapJub(MapPointer(game_object.game.size.x - SizeCut - 1, game_object.game.size.y - SizeCut - 1, collMap, xNum[8], yNum[8]), 8, collMap, blockParticleMana);
}

void Explosion::MapJub(const int& mapPoint, const int& pointNum, std::vector<std::vector<int>>& collMap, BlockParticleMana* blockParticleMana)
{
	if (pointNum == 0)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[0]][xNum[0]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[0], SIZE * yNum[0]));
			break;
		case 40:
			collMap[yNum[0]][xNum[0]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[0], SIZE * yNum[0]));
			break;
		default:
			break;
		}
	}
	else if (pointNum == 1)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[1]][xNum[1]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[1], SIZE * yNum[1]));
			break;
		case 40:
			collMap[yNum[1]][xNum[1]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[1], SIZE * yNum[1]));
			break;
		default:
			break;
		}
	}
	else if (pointNum == 2)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[2]][xNum[2]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[2], SIZE * yNum[2]));
			break;
		case 40:
			collMap[yNum[2]][xNum[2]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[2], SIZE * yNum[2]));
			break;
		default:
			break;
		}
	}
	else if (pointNum == 3)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[3]][xNum[3]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[3], SIZE * yNum[3]));
			break;
		case 40:
			collMap[yNum[3]][xNum[3]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[3], SIZE * yNum[3]));
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 4))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[4]][xNum[4]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[4], SIZE * yNum[4]));
			break;
		case 40:
			collMap[yNum[4]][xNum[4]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[4], SIZE * yNum[4]));
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 5))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[5]][xNum[5]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[5], SIZE * yNum[5]));
			break;
		case 40:
			collMap[yNum[5]][xNum[5]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[5], SIZE * yNum[5]));
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 6))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[6]][xNum[6]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[6], SIZE * yNum[6]));
			break;
		case 40:
			collMap[yNum[6]][xNum[6]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[6], SIZE * yNum[6]));
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 7))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[7]][xNum[7]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[7], SIZE * yNum[7]));
			break;
		case 40:
			collMap[yNum[7]][xNum[7]] = 41;
			break;
		default:
			break;
		}
	}
	else if ((pointNum == 8))
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[8]][xNum[8]] = 0;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[8], SIZE * yNum[8]));
			break;
		case 40:
			collMap[yNum[8]][xNum[8]] = 41;
			blockParticleMana->Spawn(Vector2(SIZE * xNum[8], SIZE * yNum[8]));
			break;
		default:
			break;
		}
	}
}

void Explosion::Draw(const Vector2& sc, const Vector2& shake, const int* exTex, const int& box)
{
	for (int i = 0; i < EXNUM; ++i)
	{
		if (exs[i].game.dis)
		{
			SetBright(exs[i].color);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)exs[i].game.pal);
			DrawRotaTex(exs[i], exTex[exAni.num], true, shake, sc);
		}
	}
	SetDrawBright(255, 255, 255);
	for (int i = 0; i < (int)boxObj.size(); ++i)
	{
		SetBright(boxObj[i].color);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)boxObj[i].game.pal);
		DrawRotaTex(boxObj[i], box, true, shake, sc);
	}
	SetBright();
	//DrawRotaTex(game_object, exTex[exAni.num], true, shake, sc);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
