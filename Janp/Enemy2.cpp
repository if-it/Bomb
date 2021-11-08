#include "Enemy2.h"

Enemy2::Enemy2()
{
	game_object = GameObject("Enemy2Tex", false, Vector2(192, 192));
	spawn = false;
	die = false;
	move = false;
	attack_Fist_Time = Count();
	attack_End_Time = Count();
	rush_Time = Count();
	attack_front_flame = false;
	arm = GameObject("Enemy2", false, Vector2(32, 128));
	arm.color = COLOR(255, 0, 0);
	attack_Animetion_flg = 3;
	body = GameObject("Enemy2", false, Vector2(160, 160));
	body.color = COLOR(255, 150, 50);
	ani = Animation();
	uturn[0] = false;
	uturn[1] = false;
}

Enemy2::~Enemy2()
{
}

void Enemy2::Init(std::vector<std::vector<int>>& collMap, Load* load, int vol)
{
	
	spawn = die;
	game_object = GameObject("Enemy2Tex", false, Vector2(240, 192));
	spawn = false;
	die = false;
	move = false;
	attack_Fist_Time = Count();
	attack_End_Time = Count();
	rush_Time = Count();
	attack_Second_Time = Count();
	attack_front_flame = false;
	arm = GameObject("Enemy2", false, Vector2(32, 128));
	arm.color = COLOR(255, 0, 0);
	attack_Animetion_flg = 100;
	first_Attack = false;
	body = GameObject("Enemy2", false, Vector2(160, 160));
	body.color = COLOR(255, 150, 50);
	ani = Animation();
	uturn[0] = false;
	uturn[1] = false;
	rock_Num = 0;
	rock_Max_Num = 8;
	die_Ex = Count();
	die_Ex_Num = 0;
	die_Ex_Max_Num = 0;
	ex_End = false;
	ex_on = 0;
	rush_Count = 0;
	if (!spawn)
	{
		for (int y = 0; y < (int)collMap.size(); ++y)
		{
			for (int x = 0; x < (int)collMap[y].size(); ++x)
			{
				if (collMap[y][x] == 101)
				{
					AllInit(103, x, y);
					load->LoadAnimeTex("Load/Texture/Enemy/Enemy2/Enemy2w.png", 21, 21, 1, 240, 192, enemy2Tex);
					load->LoadAnimeTex("Load/Texture/Enemy/Enemy2/Enemy2_Attack.png", 7, 7, 1, 240, 192, attackTex);
					load->LoadSound("Load/Sound/SE/daipan.wav", daipanSE);
					ChangeVolumeSoundMem(vol, daipanSE);
					hp = MAX_HP;
					//spawn = true;
					game_object.game.allVec.pos = Vector2(SIZE * x, SIZE * y);
					game_object.game.dis = true;
					attack_Fist_Time = Count();

					arm.game.dis = false;
					arm.SetPos(Vector2(game_object.GetPos().x - 32, game_object.GetPos().y + 32));

					body.game.dis = true;
					body.SetPos(Vector2(game_object.GetPos().x + 32, game_object.GetPos().y + 32));
					ani = Animation();
					tex = enemy2Tex[0];
					break;
				}
			}
		}
	}
}

void Enemy2::Update(const Vector2& pos, Collision* coll, bool& shake_flg, const Vector2& sc, RockAttackMana* rockAttackMana, ExplosionMana* ex)
{
	if (game_object.game.dis)
	{
		if (!die)
		{
			float max_speed = 0.0f;
			float flame_speed = 0.0f;
			bool lr = game_object.game.lr;
			attack_front_flame = attack_Fist_Time.flg;

			body.game.lr = lr;
			arm.game.lr = lr;



			if (lr)body.SetPos(Vector2(game_object.GetPos().x + 64, game_object.GetPos().y + 32));
			else body.SetPos(Vector2(game_object.GetPos().x + 8, game_object.GetPos().y + 32));

			if (lr)arm.SetPos(Vector2(game_object.GetPos().x + 32, game_object.GetPos().y + 64));
			else arm.SetPos(Vector2(game_object.GetPos().x + game_object.game.size.x - 64, game_object.GetPos().y + 64));


			int attackAniNum[7] = { 2,2,2,2,25,5,7 };
			switch (attack_Animetion_flg)
			{
			case 0:
				max_speed = 5.4f;
				flame_speed = 0.2f;
				if (attack_Fist_Time.Conuter(28))
				{
					attack_Animetion_flg = 1;
					attack_Fist_Time = Count();
					attack_Second_Time = Count();
				}
				attack_Second_Time.flg = true;
				if (attack_Second_Time.Conuter(180))
				{
					attack_Animetion_flg = 1;
					attack_Fist_Time = Count();
					attack_Second_Time = Count();
				}
				arm.game.dis = false;
				tex = enemy2Tex[ani.num];
				ani.AnimationOn(4, 21);
				break;
			case 1://近づいて殴る
				max_speed = 5.4f;
				flame_speed = 0.2f;
				arm.game.dis = true;
				tex = attackTex[attackAni.num];
				if (attackAni.OneAnimation(attackAniNum[attackAni.num], 6))
				{
					attackAni = Animation();
					attack_Animetion_flg = 5;
					arm.game.dis = false;
					tex = enemy2Tex[0];
				}
				break;
			case 2://落石
				arm.game.dis = true;
				tex = attackTex[attackAni.num];
				if (attackAni.OneAnimation(attackAniNum[attackAni.num], 6))
				{
					attackAni = Animation();
					attack_Animetion_flg = 3;
					tex = enemy2Tex[0];
					shake_flg = true;
					arm.game.dis = false;
					PlaySoundMem(daipanSE, DX_PLAYTYPE_BACK, true);
				}
				break;
			case 3:
				if (!attack_Second_Time.flg)
				{
					rock_Num += GetRand(9) + 7;
					rockAttackMana->Spawn(rock_Num, sc);
					attack_Second_Time.flg = true;
				}
				if (attack_Second_Time.Conuter(60))
				{
					rock_Num = 0;
					attack_Second_Time = Count();
					attack_Animetion_flg = 5;
				}
				break;
			case 4://突進
				++rush_Count;
				game_object.color = COLOR(255, 200, 200);
				if (rush_Count >= 90)
				{
					rush_Count = 0;
					attack_Animetion_flg = 7;
				}
				break;
			case 5:
				attack_End_Time.flg = true;
				if (hp > (int)(MAX_HP / 2))
				{
					if (attack_End_Time.Conuter(20))
					{
						attack_End_Time = Count();
						int rand = GetRand(9);
						if ((rand >= 4 && rand <= 9))
						{
							attack_Animetion_flg = 0;
						}
						else if (rand >= 0 && rand <= 3)
						{
							attack_Animetion_flg = 2;
						}
					}
				}
				else
				{
					rock_Max_Num = 10;
					if (attack_End_Time.Conuter(10))
					{
						attack_End_Time = Count();
						int rand = GetRand(10);
						if (rand >= 4 && rand <= 6)
						{
							attack_Animetion_flg = 0;
						}
						else if (rand >= 0 && rand <= 3)
						{
							attack_Animetion_flg = 2;
						}
						else if (rand >= 7 && rand <= 10)
						{
							attack_Animetion_flg = 4;
							rush_Time.flg = true;
						}
					}
				}

				break;
			case 6:
				attack_Animetion_flg = 5;
				break;
			case 7:
				game_object.color = COLOR();
				rush_Count = 0;
				tex = enemy2Tex[ani.num];
				ani.AnimationOn(2, 21);

				max_speed = 10.8f;
				flame_speed = 0.2f;

				if (uturn[0])lr = false;
				if (uturn[1])lr = true;

				if (lr)game_object.game.allVec.vec.x -= 6.0f;
				else game_object.game.allVec.vec.x += 6.0f;

				if (rush_Time.Conuter(40))
				{
					attack_Animetion_flg = 5;
				}
				break;
			default:
				break;
			}

			EnemyAllUpdate(flame_speed, max_speed);
			PlayerCahck(pos, coll);
			if (DieChack())
			{
				die = true;
				ex_on = 1;
				arm.game.dis = false;
				body.game.dis = false;
				die_Ex_Max_Num = GetRand(4) + 15;
				game_object.game.allVec.vec = Vector2();
				rockAttackMana->Delete_Rock();
			}
		}
		else
		{
			if (ex_on == 1)
			{

				die_Ex.flg = true;
				shake_flg = true;
				GameObject enemy2_End = game_object;
				enemy2_End.game.allVec.pos += Vector2(GetRand(240), GetRand(192));
				if (die_Ex.Conuter(10))
				{
					ex->ExSpawn(enemy2_End, 1);
					++die_Ex_Num;
				}
				if (die_Ex_Num == die_Ex_Max_Num)
				{
					ex_on = 2;

				}
			}
			else if (ex_on == 2)
			{
				game_object.game.pal -= 10;
				if (game_object.game.pal < 0)
				{
					ex_on = 3;
					ex_End = true;
				}
			}
		}
	}
}

void Enemy2::PlayerCahck(const Vector2& pos, Collision* coll)
{
	Vector2 layer = game_object.GetPos();
	const int LAYERSIZE = 128 * 10;
	const int ATAACKSIZE = 16;
	float distanceL = Vector2::Distance(Vector2(pos.x + SIZE * 2, pos.y), game_object.GetPos());
	float distanceR = Vector2::Distance(pos, Vector2(game_object.GetPos().x + game_object.game.size.x, game_object.GetPos().y));
	if (attack_Animetion_flg == 0 || attack_Animetion_flg == 100)
	{
		if (coll->Collsion(Vector2(layer.x - ATAACKSIZE, layer.y), ATAACKSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
		{
			//左
			if (attack_Animetion_flg == 0)
			{
				attack_Fist_Time.flg = true;
				game_object.game.lr = true;
				ani.num = 0;
			}
		}
		else if (coll->Collsion(Vector2(layer.x + game_object.game.size.x, layer.y), ATAACKSIZE + 16, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
		{
			//右
			if (attack_Animetion_flg == 0)
			{
				attack_Fist_Time.flg = true;
				game_object.game.lr = false;
				ani.num = 0;
			}

		}
		else
		{
			//右

			if (coll->Collsion(Vector2(layer.x + game_object.game.size.x, layer.y), LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
			{
				game_object.game.allVec.vec.x += 0.4f;
				game_object.game.lr = false;
				if (!first_Attack)
				{
					first_Attack = true;
					game_object.game.allVec.vec.x = 0;
					attack_Animetion_flg = 5;
				}
			}


			//左

			layer.x -= LAYERSIZE;
			if (coll->Collsion(layer, LAYERSIZE, game_object.game.size.y, pos, SIZE * 2, SIZE * 2))
			{
				game_object.game.allVec.vec.x -= 0.4f;
				game_object.game.lr = true;
				if (!first_Attack)
				{
					first_Attack = true;
					game_object.game.allVec.vec.x = 0;
					attack_Animetion_flg = 5;
				}
			}
		}
	}

}

void Enemy2::MapCollUpdate(std::vector<std::vector<int>>& collMap)
{
	Map_Coll(collMap);
}

void Enemy2::Map_Coll(std::vector<std::vector<int>>& collMap)
{
	//上左
	MapJub(MapPointerY(1, 1, collMap), 0);
	//上右
	MapJub(MapPointerY(game_object.game.size.x - 1, 1, collMap), 0);

	//下左
	MapJub(MapPointerY(1, game_object.game.size.y - 1, collMap), 1);
	//下右
	MapJub(MapPointerY(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 1);

	game_object.game.allVec.AddPosY();

	//右上
	MapJub(MapPointerX(game_object.game.size.x - 1, 1, collMap), 2);
	//右下
	MapJub(MapPointerX(game_object.game.size.x - 1, game_object.game.size.y - 1, collMap), 2);

	//左上
	MapJub(MapPointerX(1, 1, collMap), 3);
	//左下
	MapJub(MapPointerX(1, game_object.game.size.y - 1, collMap), 3);

	game_object.game.allVec.AddPosX();
}


void Enemy2::MapJub(const int& mapPoint, const int& pointNum)
{
	if (pointNum == 0) //Y軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}
	else if (pointNum == 1) //Y軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.y -= game_object.game.allVec.vec.y;
			game_object.game.allVec.vec.y = 0;
		}
	}

	else if (pointNum == 2)//X軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.x -= game_object.game.allVec.vec.x;
			game_object.game.allVec.vec.x = 0;
			uturn[0] = true;
		}
		else
		{
			uturn[0] = false;
		}
	}

	else if (pointNum == 3)//X軸
	{
		if (WALL)
		{
			game_object.game.allVec.vec.x -= game_object.game.allVec.vec.x;
			game_object.game.allVec.vec.x = 0;
			uturn[1] = true;
		}
		else
		{
			uturn[1] = false;
		}
	}
}

void Enemy2::Coll(std::vector<Explosion>& ex)
{
	for (int i = 0; i < (int)body.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = body.coll_Obj_List[i]->nameTag;

		if (nameTag == "ex")
		{
			if (!ex_Invincible.flg)
			{
				ex_Invincible.flg = true;

				Damage(ex[body.coll_Obj_List[i]->num].damage);
			}
			if (nameTag == "RSideEx" || nameTag == "LSideEx")
			{
				if (!ex_Invincible.flg)
				{
					ex_Invincible.flg = true;
					Damage(SIDE_EX_DAMAGE);
				}
			}
		}
	}
	for (int i = 0; i < (int)arm.coll_Obj_List.size(); ++i)
	{
		std::string nameTag = arm.coll_Obj_List[i]->nameTag;

		if (nameTag == "ex")
		{
			if (!ex_Invincible.flg)
			{
				ex_Invincible.flg = true;

				Damage(ex[arm.coll_Obj_List[i]->num].damage);
			}
			if (nameTag == "RSideEx" || nameTag == "LSideEx")
			{
				if (!ex_Invincible.flg)
				{
					ex_Invincible.flg = true;
					Damage(SIDE_EX_DAMAGE);
				}
			}
		}
	}
}


void Enemy2::Draw(const Vector2& sc, const Vector2& shake)
{
	SetBright(game_object.color);
	if (blinking)SetDrawBright(128, 128, 128);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)game_object.game.pal);
	DrawRotaTex(game_object, tex, true, shake, sc);
	SetDrawBright(255, 255, 255);
	/*Box(arm, false, shake, sc);
	Box(body, false, shake, sc);*/
}
