#include "Vector.h"
using namespace vector;
Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2::Normalize()
{
	//呼び出した構造体のベクトルの大きさでｘとｙ成分を割って単位ベクトルを取得
	float length = sqrtf((x*x) + (y*y));
	this->x /= length;
	this->y /= length;
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
	//二点間の距離を取得
	return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

float Vector2::Cross(Vector2 objPos, Vector2 lineBeginPos, Vector2 lineEndPos)
{
	//線分のベクトル成分を取得し
	//外積を求める
	Vector2 v1 = lineBeginPos - lineEndPos;
	Vector2 v2 = lineEndPos - objPos;
	return{ v1.x*v2.y - v2.x*v1.y };
}

float Vector2::Dot(Vector2 objPos, Vector2 lineBeginPos, Vector2 lineEndPos)
{
	//線分のベクトル成分を取得し
	//オブジェクトのベクトルを正規化した値から内積を求める
	Vector2 v1 = lineBeginPos - lineEndPos;
	Vector2 v2 = lineEndPos - objPos;
	v2.Normalize();
	return { v1.x*v2.x + v1.y*v2.y };
}

Vector2 vector::Vector2::Lerp(Vector2 a, Vector2 b, float c)
{
	//二点間のcの割合の位置を求める。
	//0.5なら二点間の1/2の位置　0.25なら1/4の位置
	//unityで使ったから入れた
	Vector2 v1 = a * (1 - c);


	return { v1 + b * c };
}

Vector2 Vector2::operator+(Vector2 objPos)
{
	return { x + objPos.x,y + objPos.y };
}

Vector2 Vector2::operator-(Vector2 objPos)
{
	return { x - objPos.x,y - objPos.y };
}

Vector2 vector::Vector2::operator+=(Vector2 objPos)
{
	return { x += objPos.x,y += objPos.y };
}

Vector2 vector::Vector2::operator-=(Vector2 objPos)
{
	return { x -= objPos.x,y -= objPos.y };
}

Vector2 vector::Vector2::operator*(Vector2 objPos)
{
	return  { x *objPos.x,y * objPos.y };
}

Vector2 vector::Vector2::operator*=(Vector2 objPos)
{
	return { x *= objPos.x,y *= objPos.y };
}

Vector2 vector::Vector2::operator=(Vector2 objPos)
{
	return { x = objPos.x,y = objPos.y };
}




const Vector2 vector::Vector2::operator-(Vector2 const & objPos) const
{
	return { x - objPos.x,y - objPos.y };
}
const Vector2 vector::Vector2::operator+(int const & objpos) const
{
	return { x + objpos,y + objpos };
}
const Vector2 vector::Vector2::operator-(int const & objpos) const
{
	return { x - objpos,y - objpos };
}

const Vector2 vector::Vector2::operator*(float a) const
{
	return { x * a,y * a };
}

const Vector2 vector::Vector2::operator/(float a) const
{
	return { x / a,y / a };
}

Vector2 vector::Vector2::operator+=(float a)
{
	return { x += a,y += a };
}

Vector2 vector::Vector2::operator-=(float a)
{
	return { x -= a,y -= a };
}

Vector2 vector::Vector2::operator*=(float a)
{
	return { x *= a, y *= a };
}

bool vector::Vector2::operator<(Vector2 a)
{
	if (x < a.x && y < a.y)
	{
		return true;
	}
	return false;
}

bool vector::Vector2::operator>(Vector2 a)
{
	if (x > a.x && y > a.y)
	{
		return true;
	}
	return false;
}

bool vector::Vector2::operator<=(Vector2 a)
{
	if (x <= a.x && y <= a.y)
	{
		return true;
	}
	return false;
}

bool vector::Vector2::operator>=(Vector2 a)
{
	if (x >= a.x && y >= a.y)
	{
		return true;
	}
	return false;
}

bool vector::Vector2::operator==(Vector2 objPos)
{
	if (x == objPos.x&&y == objPos.y)
	{
		return true;
	}
	return false;
}

bool vector::Vector2::operator!=(Vector2 objPos)
{
	if (x != objPos.x&&y != objPos.y)
	{
		return true;
	}
	return false;
}