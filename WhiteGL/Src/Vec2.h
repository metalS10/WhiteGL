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
	inline CVec2& CVec2::operator*=(const float& v)
	{
		multi(v);
		return *this;
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

class Size
{
public:
	/**Width of the Size.*/
	float width;
	/**Height of the Size.*/
	float height;
public:
	/**Conversion from Vec2 to Size.*/
	operator CVec2() const
	{
		return CVec2(width, height);
	}

public:
	/**
	@{
	Constructor.
	@param width Width of the size.
	@param height Height of the size.
	@param other Copy constructor.
	@param point Conversion from a point.
	*/
	Size();
	Size(float width, float height);
	Size(const Size& other);
	explicit Size(const CVec2& point);
	/**@}*/

	/**
	* @js NA
	* @lua NA
	*/
	Size& operator= (const Size& other);
	/**
	* @js NA
	* @lua NA
	*/
	Size& operator= (const CVec2& point);
	/**
	* @js NA
	* @lua NA
	*/
	Size operator+(const Size& right) const;
	/**
	* @js NA
	* @lua NA
	*/
	Size operator-(const Size& right) const;
	/**
	* @js NA
	* @lua NA
	*/
	Size operator*(float a) const;
	/**
	* @js NA
	* @lua NA
	*/
	Size operator/(float a) const;
	/**
	Set the width and height of Size.
	* @js NA
	* @lua NA
	*/
	void setSize(float width, float height);
	/**
	Check if two size is the same.
	* @js NA
	*/
	bool equals(const Size& target) const;
	/**Size(0,0).*/
	static const Size ZERO;
};