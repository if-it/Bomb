#include "MapPlayerColl.h"



MapPlayerColl::MapPlayerColl()
{
}


MapPlayerColl::~MapPlayerColl()
{
}

void MapPlayerColl::Init()
{
	sc2 = Vector2();
	vec = Vector2();
	jamp = false;
	clear = false;
	for (int i = 0;i < 5;i++)
	{
		bxNum[i] = 0;
		byNum[i] = 0;
		back_flg[i] = false;
		collFlg[i] = false;
	}
}

void MapPlayerColl::MapColl(int(*collMap)[MAPX], Vector2& sc, GameObject& chara,
	int sizeX, int sizeY, int SizeCut, bool &jampFlg, int &playerMapNum, bool &stageChange, int&stage)
{
	jamp = false;
	for (int i = 0;i < 5;++i)
	{
		back_flg[i] = false;
		collFlg[i] = false;
	}
	vec = chara.allVec.vec;

	//上左
	MapJub(MapPointer(chara.allVec, SizeCut + 1, SizeCut + 1, true, collMap, bxNum[0], byNum[0]),
		chara, 0, jampFlg, playerMapNum, stageChange, stage);
	//上右
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, SizeCut + 1, true, collMap, bxNum[0], byNum[0]),
		chara, 0, jampFlg, playerMapNum, stageChange, stage);

	//下左
	MapJub(MapPointer(chara.allVec, SizeCut + 1, sizeY - SizeCut - 1, true, collMap, bxNum[1], byNum[1]),
		chara, 1, jampFlg, playerMapNum, stageChange, stage);
	//下右
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, sizeY - SizeCut - 1, true, collMap, bxNum[1], byNum[1]),
		chara, 1, jampFlg, playerMapNum, stageChange, stage);

	chara.allVec.vec.y = vec.y;
	chara.allVec.AddPosY();

	//右上
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, SizeCut + 1, false, collMap, bxNum[2], byNum[2]),
		chara, 2, jampFlg, playerMapNum, stageChange, stage);
	//右下
	MapJub(MapPointer(chara.allVec, sizeX - SizeCut - 1, sizeY - SizeCut - 1, false, collMap, bxNum[2], byNum[2]),
		chara, 2, jampFlg, playerMapNum, stageChange, stage);

	//左上
	MapJub(MapPointer(chara.allVec, SizeCut + 1, SizeCut + 1, false, collMap, bxNum[3], byNum[3]),
		chara, 3, jampFlg, playerMapNum, stageChange, stage);
	//左下
	MapJub(MapPointer(chara.allVec, SizeCut + 1, sizeY - SizeCut - 1, false, collMap, bxNum[3], byNum[3]),
		chara, 3, jampFlg, playerMapNum, stageChange, stage);

	//中心
	MapJub(MapPointer(chara.allVec, (sizeX - SizeCut) / 2, (sizeY - SizeCut) / 2, false, collMap, bxNum[4], byNum[4]),
		chara, 4, jampFlg, playerMapNum, stageChange, stage);

	chara.allVec.vec.x = vec.x;
	chara.allVec.AddPosX();
	for (int i = 0;i < 5;++i)
	{
		if (back_flg[i])
		{
			collMap[byNum[i]][bxNum[i]] = 41;
		}
	}

	if (chara.allVec.pos.x >= WIDTH / 2 - SIZE / 2 && chara.allVec.pos.x <= (SIZE*MAPX) - WIDTH / 2 + SIZE / 2)
	{
		sc2.x += vec.x;
	}

	if (chara.allVec.pos.x < WIDTH / 2 - SIZE / 2)
	{
		sc2.x = 0;
	}
	if (chara.allVec.pos.x > (SIZE*MAPX) - WIDTH / 2 + SIZE / 2)
	{
		sc2.x = (SIZE*MAPX) - WIDTH;
	}


	if (chara.allVec.pos.y >= HEIGHT / 2 + SIZE / 2 && chara.allVec.pos.y <= (SIZE*MAPY) - HEIGHT / 2 - SIZE / 2)
	{
		sc2.y += vec.y;
	}
	if (chara.allVec.pos.y < HEIGHT / 2 + SIZE / 2)
	{
		sc2.y = 0;
	}
	if (chara.allVec.pos.y > (SIZE*MAPY) - HEIGHT / 2 - SIZE / 2)
	{
		sc2.y = (SIZE*MAPY) - HEIGHT;
	}

	sc = Vector2::Lerp(sc, sc2, 0.05f);

	jampFlg = jamp;
}

void MapPlayerColl::MapJub(int mapPoint, GameObject& chara, int XY, bool &jampFlg, int &playerMapNum, bool &stageChange, int&stage)
{
	if (XY == 0) //Y軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[0] && vec.y == 0)
			{
				back_flg[0] = true;
			}
		}
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
		{
			vec.y = 0;
			collFlg[0] = true;
		}
	}
	else if (XY == 1) //Y軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[1] && vec.y == 0)
			{
				back_flg[1] = true;
			}
		}
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
		{
			vec.y = 0;
			jamp = true;
			collFlg[1] = true;
		}
	}

	else if (XY == 2)//X軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[2] && vec.x == 0)
			{
				back_flg[2] = true;
			}
		}
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
		{
			vec.x = 0;
			collFlg[2] = true;
		}
	}

	else if (XY == 3)//X軸
	{
		if (mapPoint == 40)
		{
			if (!collFlg[3] && vec.x == 0)
			{
				back_flg[3] = true;
			}
		}
		if (mapPoint == 1 || (mapPoint >= 2 && mapPoint <= 23) || mapPoint == 40)
		{
			vec.x = 0;
			collFlg[3] = true;
		}
	}
	else if (XY == 4)//中心
	{
		switch (mapPoint)
		{
		case 25:
			playerMapNum = 35;
			stageChange = true;
			switch (stage)
			{
			case 1:
				stage = 2;
				break;
			case 2:
				stage = 1;
				break;
			case 5:
				stage = 6;
				break;
			case 6:
				stage = 5;
				break;
			default:
				break;
			}
			break;
		case 26:
			playerMapNum = 36;
			stageChange = true;
			switch (stage)
			{
			case 2:
				stage = 3;
				break;
			case 3:
				stage = 2;
				break;
			case 6:
				stage = 7;
				break;
			case 7:
				stage = 6;
				break;
			default:
				break;
			}
			break;
		case 27:
			playerMapNum = 37;
			stageChange = true;
			switch (stage)
			{
			case 3:
				stage = 4;
				break;
			case 4:
				stage = 3;
				break;
			case 7:
				stage = 8;
				break;
			case 8:
				stage = 7;
				break;
			default:
				break;
			}
			break;
		case 28:
			playerMapNum = 38;
			stageChange = true;
			switch (stage)
			{
			case 2:
				stage = 4;
				break;
			case 4:
				stage = 2;
				break;
			default:
				break;
			}
			break;
		case 29:
			playerMapNum = 39;
			stageChange = true;
			switch (stage)
			{
			case 2:
				stage = 5;
				break;
			case 5:
				stage = 2;
				break;
			default:
				break;
			}
			break;
		case 40:
			back_flg[4] = true;
			break;
		case 65:
			clear = true;
			break;
		default:
			break;
		}
	}
}
