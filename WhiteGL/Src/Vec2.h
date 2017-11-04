#pragma once

//=====================================
//
//2Dベクトルを扱うクラス
//
//=====================================
class CVec2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	CVec2(){}
	CVec2(float x,float y)
		:x(x),y(y){}
	CVec2(const CVec2& v)
		:x(v.x),y(v.y){}

	inline CVec2& CVec2::operator+=(const CVec2& v)
	{
		add(v);
		return *this;
	}
	inline CVec2& CVec2::operator+(const CVec2& v)
	{
		add2(v);
		return *this;
	}
	inline CVec2& CVec2::operator*(const float& v)
	{
		multi(v);
		return *this;
	}

	inline void CVec2::add(const CVec2& v)
	{
		x += v.x;
		y += v.y;
	}
	inline void CVec2::add2(const CVec2& v)
	{
		x += v.x;
		y += v.y;
	}
	inline void CVec2::multi(const float& v)
	{
		x *= v;
		y *= v;
	}

	inline void CVec2::set(const float vx, const float vy)
	{
		x = vx;
		y = vy;
	}
	inline void CVec2::set(const CVec2 xy)
	{
		x = xy.x;
		y = xy.y;
	}

};