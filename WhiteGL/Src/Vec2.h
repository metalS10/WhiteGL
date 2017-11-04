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
	inline CVec2 CVec2::operator+(const CVec2& v)
	{
		CVec2 result(*this);
		result.add(v);
		return result;
	}
	inline CVec2 CVec2::operator*(const float& v) const
	{
		CVec2 result(*this);
		result.multi(v);
		return result;
	}

	inline void CVec2::add(const CVec2& v)
	{
		x += v.x;
		y += v.y;
	}
	void CVec2::add(const CVec2& v1, const CVec2& v2, CVec2* dst)
	{

		dst->x = v1.x + v2.x;
		dst->y = v1.y + v2.y;
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