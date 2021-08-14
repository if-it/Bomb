#pragma once
#include"Parent.h"
#include<string>
class Structure
{
public:
	Structure();
	~Structure();
protected:
	struct ALLVECTOR
	{
		Vector2 pos;
		Vector2 vec;
		Vector2 ang;

		ALLVECTOR(Vector2 poss = Vector2(), Vector2 vecs = Vector2(), Vector2 angs = Vector2())
		{
			pos = poss;
			vec = vecs;
			ang = angs;
		}
		void AddPos()
		{
			pos += vec;
		}
		void AddPosX()
		{
			pos.x += vec.x;
		}
		void AddPosY()
		{
			pos.y += vec.y;
		}
	};
	struct Count
	{
		int count;
		bool flg;
		Count(bool flgSet = false)
		{
			count = 0;
			flg = flgSet;
		}
		bool Conuter(int maxCount)
		{
			if (flg)
			{
				count++;
				if (count >= maxCount)
				{
					flg = false;
					count = 0;
					return true;
				}
			}
			return false;
		}
	};
	struct Animation
	{
		Count counter;
		int num;
		bool oneAnimeFlg;
		bool round;
		Animation()
		{
			counter = Count(true);
			num = 0;
			oneAnimeFlg = false;
			round = false;
		}
		void AnimationOn(int maxCount, int maxNum, int lowNum = 0)
		{
			if (counter.Conuter(maxCount))
			{
				counter.flg = true;
				num++;
				if (num >= maxNum)
				{
					num = lowNum;
				}
			}

		}
		bool OneAnimation(int maxCount, int maxNum)
		{
			if (!oneAnimeFlg)
			{
				if (!counter.flg)
				{
					counter.flg = true;
					num++;
					if (num >= maxNum)
					{
						num--;
						oneAnimeFlg = true;
						return oneAnimeFlg;
					}
				}
				counter.Conuter(maxCount);
			}
			return oneAnimeFlg;
		}
		void Round_Trip_Animation(int maxCount, int maxNum, int lowNum = 0)
		{
			if (counter.Conuter(maxCount))
			{
				counter.flg = true;
				if (!round)
				{
					num++;
					if (num >= maxNum)
					{
						num--;
						round = true;
					}
				}
				else
				{
					num--;
					if (num < lowNum)
					{
						num++;
						round = false;
					}
				}
			}
		}
	};
	struct COLOR
	{
		int red;
		int green;
		int blue;
		COLOR(int r = 0, int g = 0, int b = 0)
		{
			red = r;
			green = g;
			blue = b;
		}
	};
	//ゲームに必要な基礎変数
	struct Game
	{
		std::string nameTag;
		ALLVECTOR allVec;
		Vector2 scale;
		Vector2 texSize;
		Vector2 size;
		bool dis;
		bool lr;
		float rota;
		float pal;
		int num;
		Game(const std::string& NameTag = "noName",
			const bool& disFlg = true, const Vector2& TexSize = Vector2(32.0f, 32.0f), const Vector2& Scale = Vector2(1.0f, 1.0f))
		{

			nameTag = NameTag;
			allVec = ALLVECTOR();
			scale = Scale;
			texSize = TexSize;
			size = texSize * scale;
			dis = disFlg;
			lr = false;
			rota = 0;
			pal = 255;
			num = 0;
		}
	};
	//上をもとに当たり判定の簡易化などを加えたもの
	struct GameObject
	{

		Game game;
		COLOR color;
		//当たり判定リスト
		std::vector<Game*>coll_Obj_List;
		bool same;

		GameObject(const std::string& NameTag = "noName", const bool& disFlg = true,
			const Vector2& TexSize = Vector2(32.0f, 32.0f), const Vector2& Scale = Vector2(1.0f, 1.0f), const bool& Same = false)
		{

			game = Game(NameTag, disFlg, TexSize, Scale);
			color = COLOR();
			coll_Obj_List.clear();
			same = Same;
		}

		Vector2 GetPos() { return game.allVec.pos; }
		void SetPos(Vector2 pos) { game.allVec.pos = pos; }
	};
	void SizeChange(Count& count, Vector2& size, Vector2 change, int maxCount);
	void AnimeEnd(Count& ani, int maxCount, Vector2& size, Vector2 sizeNum);
	void SetBright(COLOR color = COLOR(255, 255, 255));
	unsigned int MyGetColor(COLOR color);
public:
	GameObject game_object;

};

