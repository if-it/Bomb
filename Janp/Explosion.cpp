#include "Explosion.h"

Explosion::Explosion()
{
}

Explosion::~Explosion()
{
}

void Explosion::Init()
{
	boxObj.clear();
	boxTime.clear();
	boxFlg.clear();
	game_object = GameObject(false, Vector2(64.0f, 64.0f));
	exAni = ANIMATION();
	spawn = false;
	time = 0;
	//game_object.allVec.pos = go.allVec.pos;
	for (int i = 0; i < EXNUM; ++i)
	{
		exs[i] = GameObject(false, Vector2(16.0f, 16.0f));
	}

}

void Explosion::Update()
{
	if (game_object.dis)
	{
		if (!spawn)
		{

			Vector2 spos = game_object.allVec.pos;

			spawn = true;
			for (int i = 0; i < EXNUM; ++i)
			{
				exs[i].dis = true;
				exs[i].allVec.pos = Vector2((float)(spos.x + GetRand(game_object.size.x / 2)),
					(float)(spos.y + GetRand(game_object.size.y / 2)));
				exs[i].allVec.vec = Vector2((float)GetRand(3) - (float)GetRand(3), (float)GetRand(3) - (float)GetRand(3));
			}
			for (int i = 0; i < BOXNUM; ++i)
			{
				boxTime.push_back(0);
				boxFlg.push_back(true);
				GameObject InitBox;
				InitBox = GameObject(true, Vector2(1.0f, 1.0f), Vector2(4.0f, 4.0f));
				InitBox.allVec.pos = Vector2((float)(spos.x + game_object.size.x / 2), (float)(spos.y + game_object.size.y / 2));
				InitBox.allVec.vec = exs[i].allVec.vec = Vector2((float)GetRand(3) - (float)GetRand(3), -(float)(GetRand(2) + 1));
				InitBox.pal = 255;
				InitBox.color = COLOR();
				boxObj.push_back(InitBox);
			}
		}
		else
		{
			for (int i = 0; i < EXNUM; ++i)
			{
				//exs[i].allVec.AddPos();
				exs[i].pal -= 3;
			}
			for (int i = 0; i < (int)boxObj.size(); ++i)
			{
				if (!boxFlg[i])boxObj[i].pal -= 3;
				else {
					boxObj[i].allVec.vec.y += 0.1f;
					boxObj[i].allVec.AddPos();
					boxTime[i]++;
				}
				if (boxTime[i] == 2)
				{
					boxTime[i] = 0;
					boxTime.push_back(0);
					boxFlg.push_back(false);
					GameObject box2 = GameObject();
					box2 = boxObj[i];
					box2.pal = 120;
					box2.color = COLOR(120, 120, 120);
					boxObj.push_back(box2);

				}
			}
			if (exAni.OneAnimation(5, 12))
			{
				for (int i = 0; i < EXNUM; ++i)
				{
					exs[i] = GameObject(false);
				}
				game_object = GameObject(false);
				boxObj.clear();
				boxTime.clear();
				boxFlg.clear();
			}
		}
	}
}

void Explosion::Map_Coll_Update(std::vector<std::vector<int>>& collMap)
{
	if (game_object.dis)Map_Coll(collMap);
}

void Explosion::Coll(Collision* coll, ALLVECTOR all, Vector2 size)
{
}

void Explosion::Draw(const Vector2& sc, const Vector2& shake, const int* exTex, const int& box)
{
	for (int i = 0; i < EXNUM; ++i)
	{
		if (exs[i].dis)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)exs[i].pal);
			DrawRotaTex(exs[i], exTex[exAni.num], true, shake, sc);
		}
	}
	for (int i = 0; i < (int)boxObj.size(); ++i)
	{
		SetBright(boxObj[i].color);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)boxObj[i].pal);
		DrawRotaTex(boxObj[i], box, true, shake, sc);
	}
	SetBright();
	//DrawRotaTex(game_object, exTex[exAni.num], true, shake, sc);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Explosion::Map_Coll(std::vector<std::vector<int>>& collMap)
{
	static int SizeCut = 0;
	//上左
	MapJub(MapPointer(SizeCut + 1, SizeCut + 1, collMap, xNum[0], yNum[0]), 0, collMap);

	//上真ん中
	MapJub(MapPointer(game_object.size.x / 2, SizeCut + 1, collMap, xNum[1], yNum[1]), 1, collMap);

	//上右
	MapJub(MapPointer(game_object.size.x - SizeCut - 1, SizeCut + 1, collMap, xNum[2], yNum[2]), 2, collMap);

	//右真ん中
	MapJub(MapPointer(game_object.size.x - SizeCut - 1, game_object.size.y / 2, collMap, xNum[3], yNum[3]), 3, collMap);

	//中心
	MapJub(MapPointer((game_object.size.x - SizeCut) / 2, (game_object.size.y - SizeCut) / 2, collMap, xNum[4], yNum[4]), 4, collMap);

	//左真ん中
	MapJub(MapPointer(SizeCut + 1, game_object.size.y / 2, collMap, xNum[5], yNum[5]), 5, collMap);

	//下左
	MapJub(MapPointer(SizeCut + 1, game_object.size.y - SizeCut - 1, collMap, xNum[6], yNum[6]), 6, collMap);

	//下真ん中
	MapJub(MapPointer(game_object.size.x / 2, game_object.size.y - SizeCut - 1, collMap, xNum[7], yNum[7]), 7, collMap);

	//下右
	MapJub(MapPointer(game_object.size.x - SizeCut - 1, game_object.size.y - SizeCut - 1, collMap, xNum[8], yNum[8]), 8, collMap);
}

void Explosion::MapJub(const int& mapPoint, const int& pointNum, std::vector<std::vector<int>>& collMap)
{
	if (pointNum == 0)
	{
		switch (mapPoint)
		{
		case 3:
			collMap[yNum[0]][xNum[0]] = 0;
			break;
		case 40:
			collMap[yNum[0]][xNum[0]] = 41;
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
			break;
		case 40:
			collMap[yNum[1]][xNum[1]] = 41;
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
			break;
		case 40:
			collMap[yNum[2]][xNum[2]] = 41;
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
			break;
		case 40:
			collMap[yNum[3]][xNum[3]] = 41;
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
			break;
		case 40:
			collMap[yNum[4]][xNum[4]] = 41;
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
			break;
		case 40:
			collMap[yNum[5]][xNum[5]] = 41;
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
			break;
		case 40:
			collMap[yNum[6]][xNum[6]] = 41;
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
			break;
		case 40:
			collMap[yNum[8]][xNum[8]] = 41;
			break;
		default:
			break;
		}
	}
}
