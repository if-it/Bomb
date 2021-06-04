#pragma once
#include"Parent.h"
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
		void Conuter(int maxCount)
		{
			if (flg)
			{
				count++;
				if (count >= maxCount)
				{
					flg = false;
					count = 0;
				}
			}
		}
	};
	struct ANIMATION
	{
		Count counter;
		int num;
		bool oneAnimeFlg;
		ANIMATION()
		{
			counter = Count(true);
			num = 0;
			oneAnimeFlg = false;
		}
		void Animation(int maxCount, int maxNum)
		{
			if (!counter.flg)
			{
				counter.flg = true;
				num++;
				if (num == maxNum)
				{
					num = 0;
				}
			}
			counter.Conuter(maxCount);
		}
		bool OneAnimation(int maxCount, int maxNum)
		{
			if (!oneAnimeFlg)
			{
				if (!counter.flg)
				{
					counter.flg = true;
					num++;
					if (num == maxNum)
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


	struct GameObject
	{
		ALLVECTOR allVec;
		COLOR color;
		Vector2 scale;
		Vector2 texSize;
		Vector2 size;
		bool dis;
		bool lr;
		float rote;
		float pal;

		GameObject(bool disFlg = true)
		{
			allVec = ALLVECTOR();
			color = COLOR();
			scale = Vector2(1.0f, 1.0f);
			texSize = Vector2(32.0f, 32.0f);
			size = texSize * scale;
			dis = disFlg;
			lr = false;
			rote = 0;
			pal = 255;
		}
	};
	GameObject game_object;
	void SizeChange(Count &count, Vector2&size, Vector2 change, int maxCount);
	void AnimeEnd(Count&ani, int maxCount, Vector2&size, Vector2 sizeNum);
	void SetBright(COLOR color = COLOR(255, 255, 255));
	unsigned int MyGetColor(COLOR color);
};

